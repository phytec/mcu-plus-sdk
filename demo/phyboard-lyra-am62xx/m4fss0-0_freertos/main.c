/*
 *  Copyright (C) 2024 PHYTEC
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <drivers/sciclient.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include "common.h"

#define MAIN_TASK_PRI               (configMAX_PRIORITIES-1)
#define GPIO_LED_BLINK_TASK_PRI     (tskIDLE_PRIORITY + 2)
#define LPM_SUSPEND_TASK_PRI        (tskIDLE_PRIORITY + 3)

#define GPIO_STACK_SIZE (1024U)
uint8_t gpio_xStack[GPIO_STACK_SIZE] __attribute__((aligned(32)));

#define LPM_SUSPEND_STACK_SIZE (1024U)
uint8_t lpm_suspend_xStack[LPM_SUSPEND_STACK_SIZE] __attribute__((aligned(32)));

#define MAIN_TASK_SIZE (16384U/sizeof(configSTACK_DEPTH_TYPE))
StackType_t gMainTaskStack[MAIN_TASK_SIZE] __attribute__((aligned(32)));

StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;

void gpio_led_blink(void *args);

volatile uint8_t gbShutdown = 0u;
volatile uint8_t gbShutdownRemotecoreID = 0u;
volatile uint8_t gbSuspendRemotecoreID = 0u;

SemaphoreP_Object gLpmSuspendSem;

void ipc_rp_mbox_callback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
{
    if (clientId == IPC_NOTIFY_CLIENT_ID_RP_MBOX)
    {
        if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN) /* Shutdown request from the remotecore */
        {
            gbShutdown = 1u;
            gbShutdownRemotecoreID = remoteCoreId;
        }
        else if (msgValue == IPC_NOTIFY_RP_MBOX_SUSPEND_SYSTEM) /* Linux is entering a low power mode */
        {
            gbSuspendRemotecoreID = remoteCoreId;
            SemaphoreP_post(&gLpmSuspendSem);
        }
        else if (msgValue == IPC_NOTIFY_RP_MBOX_ECHO_REQUEST) /* Linux resumed while this core stayed on */
        {
            IpcNotify_sendMsg(remoteCoreId, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                              IPC_NOTIFY_RP_MBOX_ECHO_REPLY, 1u);
        }
    }
}

/*
 * Linux waits for a reply to every suspend request. Without one it suspends
 * anyway, but never shuts this core down or restarts it on resume.
 */
void lpm_suspend(void *args)
{
    int32_t status;
    uint8_t nextHostState;
    uint32_t reply;

    while(1)
    {
        SemaphoreP_pend(&gLpmSuspendSem, SystemP_WAIT_FOREVER);

        /* The DM knows whether the MCU domain stays powered in this low power mode */
        status = Sciclient_lpmGetNextHostState(SystemP_WAIT_FOREVER, &nextHostState);
        if (status != SystemP_SUCCESS)
            nextHostState = TISCI_MSG_VALUE_HOST_STATE_INVALID;

        switch (nextHostState)
        {
            case TISCI_MSG_VALUE_HOST_STATE_OFF:
                /* Linux sends a shutdown request next and reloads the firmware on resume */
                reply = IPC_NOTIFY_RP_MBOX_SUSPEND_ACK;
                break;
            case TISCI_MSG_VALUE_HOST_STATE_ON:
                /* MCU only mode, keep running while Linux is suspended */
                reply = IPC_NOTIFY_RP_MBOX_SUSPEND_AUTO;
                break;
            default:
                reply = IPC_NOTIFY_RP_MBOX_SUSPEND_CANCEL;
                break;
        }

        DebugP_log("Suspend request, next host state %d\r\n", nextHostState);

        IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, reply, 1u);
    }
}

void freertos_main(void *args)
{
    int32_t status;
    TaskP_Params taskParams;
    TaskP_Object gpioTask;
    TaskP_Object lpmSuspendTask;

    Drivers_open();
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

#ifndef _DEBUG_
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status==SystemP_SUCCESS);
#endif

    status = SemaphoreP_constructBinary(&gLpmSuspendSem, 0);
    DebugP_assert(status==SystemP_SUCCESS);

    status = IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, &ipc_rp_mbox_callback, NULL);
    DebugP_assert(status==SystemP_SUCCESS);

    DebugP_log("PHYTEC Demo Firmware\r\n");

    TaskP_Params_init(&taskParams);
    taskParams.name = "lpm_suspend";
    taskParams.stackSize = LPM_SUSPEND_STACK_SIZE;
    taskParams.stack = lpm_suspend_xStack;
    taskParams.priority = LPM_SUSPEND_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = lpm_suspend;

    status = TaskP_construct(&lpmSuspendTask, &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&taskParams);
    taskParams.name = "gpio_led_blink";
    taskParams.stackSize = GPIO_STACK_SIZE;
    taskParams.stack = gpio_xStack;
    taskParams.priority = GPIO_LED_BLINK_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = gpio_led_blink;

    status = TaskP_construct(&gpioTask, &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    while(!gbShutdown)
        vTaskDelay(SEC_TO_TICKS(1));

    Board_driversClose();
    Drivers_close();

    IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                      IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1u);

    __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");

    vTaskDelete(NULL);
}

int main()
{
    /* init SOC specific modules */
    System_init();
    Board_init();

    /* This task is created at highest priority, it should create more tasks and then delete itself */
    gMainTask = xTaskCreateStatic( freertos_main,   /* Pointer to the function that implements the task. */
                                  "freertos_main", /* Text name for the task.  This is to facilitate debugging only. */
                                  MAIN_TASK_SIZE,  /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,            /* We are not using the task parameter. */
                                  MAIN_TASK_PRI,   /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gMainTaskStack,  /* pointer to stack base */
                                  &gMainTaskObj ); /* pointer to statically allocated task object memory */
    configASSERT(gMainTask != NULL);

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();

    /* The following line should never be reached because vTaskStartScheduler()
    will only return if there was not enough FreeRTOS heap memory available to
    create the Idle and (if configured) Timer tasks.  Heap management, and
    techniques for trapping heap exhaustion, are described in the book text. */
    DebugP_assertNoLog(0);

    return 0;
}

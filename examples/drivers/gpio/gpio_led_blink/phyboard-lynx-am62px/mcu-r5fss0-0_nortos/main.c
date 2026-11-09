/*
 *  Copyright (C) 2023-2025 Texas Instruments Incorporated
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
#include <drivers/sciclient.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

void gpio_led_blink_main(void *args);

/* Makes the blink loop return so main can handle a request */
volatile uint8_t gbWake = 0u;
volatile uint8_t gbShutdown = 0u;
volatile uint16_t gbShutdownRemotecoreID = 0u;
volatile uint8_t gbSuspend = 0u;
volatile uint16_t gbSuspendRemotecoreID = 0u;

static void ipc_rp_mbox_callback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
{
    if (clientId != IPC_NOTIFY_CLIENT_ID_RP_MBOX)
    {
        return;
    }

    if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN)
    {
        gbShutdownRemotecoreID = remoteCoreId;
        gbShutdown = 1u;
        gbWake = 1u;
    }
    else if (msgValue == IPC_NOTIFY_RP_MBOX_SUSPEND_SYSTEM)
    {
        /* The reply needs Sciclient, which can't be used from this ISR */
        gbSuspendRemotecoreID = remoteCoreId;
        gbSuspend = 1u;
        gbWake = 1u;
    }
    else if (msgValue == IPC_NOTIFY_RP_MBOX_ECHO_REQUEST)
    {
        /* Linux resumed while this core stayed on */
        IpcNotify_sendMsg(remoteCoreId, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                          IPC_NOTIFY_RP_MBOX_ECHO_REPLY, 1u);
    }
}

/*
 * Linux waits for a reply to every suspend request. Without one it keeps
 * this core powered and never shuts it down or restarts it on resume.
 */
static void lpm_suspend_reply(void)
{
    uint8_t nextHostState;
    uint32_t reply;

    /* The DM knows whether the MCU domain stays powered in this low power mode */
    if (Sciclient_lpmGetNextHostState(SystemP_WAIT_FOREVER, &nextHostState) != SystemP_SUCCESS)
    {
        nextHostState = TISCI_MSG_VALUE_HOST_STATE_INVALID;
    }

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

    /* Log before replying, IO isolation may be enabled right after */
    DebugP_log("Suspend request, next host state %d\r\n", nextHostState);

    IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, reply, 1u);
}

int main()
{
    int32_t status = SystemP_SUCCESS;

    System_init();
    Board_init();

    /* Open drivers */
    Drivers_open();
    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    /* Linux sends SHUTDOWN on remoteproc stop and waits for the ACK */
    status = IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, ipc_rp_mbox_callback, NULL);
    DebugP_assert(status==SystemP_SUCCESS);

    /* Blink until a shutdown is requested, handling suspend requests in between */
    while(gbShutdown == 0u)
    {
        gpio_led_blink_main((void *) &gbWake);

        /* Clear first, so a request arriving now runs the loop again */
        gbWake = 0u;
        if (gbSuspend != 0u)
        {
            gbSuspend = 0u;
            lpm_suspend_reply();
        }
    }

    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    Board_deinit();
    /* Also stops the tick timer and disables interrupts */
    System_deinit();

    IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                      IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1u);

    /* Linux halts the core once it is in WFI */
    while(1)
    {
        __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");
    }
}

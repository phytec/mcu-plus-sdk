/*
 *  Copyright (C) 2023-25 Texas Instruments Incorporated
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
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

void gpio_led_blink_main(void *args);

/* Also makes the blink loop return */
volatile uint8_t gbShutdown = 0u;
volatile uint16_t gbShutdownRemotecoreID = 0u;

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
    }
    else if (msgValue == IPC_NOTIFY_RP_MBOX_SUSPEND_SYSTEM)
    {
        /*
         * The J722S DM has no MCU only mode, so this core can't stay on while
         * Linux is suspended. After the ACK Linux shuts it down and reloads it
         * on resume. Without a reply it waits 5s and keeps the core powered.
         */
        IpcNotify_sendMsg(remoteCoreId, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                          IPC_NOTIFY_RP_MBOX_SUSPEND_ACK, 1u);
    }
}

int main()
{
    int32_t status = SystemP_SUCCESS;

    System_init();
    Board_init();

    /* Open drivers */
    Drivers_open();
    /* Open board component drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    /* Linux sends SHUTDOWN on remoteproc stop and waits for the ACK */
    status = IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, ipc_rp_mbox_callback, NULL);
    DebugP_assert(status==SystemP_SUCCESS);

    gpio_led_blink_main((void *) &gbShutdown);

    /* Close boards memory drivers */
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

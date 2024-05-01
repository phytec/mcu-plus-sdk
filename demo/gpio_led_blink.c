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

#include <drivers/gpio.h>

#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "common.h"


extern volatile uint8_t gbShutdown;

void gpio_led_blink(void *args)
{
    uint32_t gpioBaseAddr, pinNum;

    DebugP_log("Start gpio_led_blink task\r\n");

    gpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_LED_BASE_ADDR);
    pinNum = GPIO_LED_PIN;

    GPIO_setDirMode(gpioBaseAddr, pinNum, GPIO_LED_DIR);
    while(!gbShutdown)
    {
        GPIO_pinWriteHigh(gpioBaseAddr, pinNum);
        vTaskDelay(MSEC_TO_TICKS(100));
        GPIO_pinWriteLow(gpioBaseAddr, pinNum);
        vTaskDelay(MSEC_TO_TICKS(250));
        GPIO_pinWriteHigh(gpioBaseAddr, pinNum);
        vTaskDelay(MSEC_TO_TICKS(100));
        GPIO_pinWriteLow(gpioBaseAddr, pinNum);

        vTaskDelay(SEC_TO_TICKS(1));
    }

    vTaskDelete(NULL);
}

/*
 ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include <i2c_master.h>
#include "ch.h"
#include "hal.h"
#include "picoc_threads.h"
#include "picoc.h"
#include "rs232.h"
#include "switch_master.h"

extern void usb_init(void);

/*
 * Application entry point.
 */
int main(void)
{

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();
	chRegSetThreadName("main");

	palSetPadMode(GPIOD, 14, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOD, 13, PAL_MODE_OUTPUT_PUSHPULL);
	usb_init();
	picoc_threads_init();

	//board init
	serial_init();
	switch_masterGpioInit();
	i2c_init(&I2CD1);

	while (TRUE)
	{
		picoc_threads_loop();
		chThdSleepMilliseconds(500);
	}
}

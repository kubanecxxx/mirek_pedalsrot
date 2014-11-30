/**
 * @file input_mgt.c
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "i2c_buttons.h"
#include "input_mgt.h"
#include "picoc_threads.h"
#include <string.h>
#include "i2c_harmonist.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EVENT_I2C_BUTTONS 8
#define EVENT_HARMONIZER_BUTTON 16
#define EVENT_TEST_BUTTON 32

#define HARM_PORT GPIOA
#define HARM_PIN  0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static THD_WORKING_AREA(input_mgt_wa,512);
static thread_t * thd;

/* Private function prototypes -----------------------------------------------*/

static msg_t input_mgt_thd(void * arg);
/* Private functions ---------------------------------------------------------*/

void input_mgt_init(void)
{
	thd = chThdCreateStatic(&input_mgt_wa, sizeof(input_mgt_wa), NORMALPRIO,
			input_mgt_thd,
			NULL);
	i2c_buttons_cons_thread(thd, EVENT_I2C_BUTTONS);
	harm_set_cons_thread(thd, EVENT_HARMONIZER_BUTTON);

	palSetPadMode(HARM_PORT, HARM_PIN, PAL_MODE_INPUT_PULLDOWN);
}

msg_t input_mgt_thd(void * arg)
{
	(void) arg;
	msg_t buttons;
	static footswitch_picoc_data_t footswitch;
	memset(&footswitch, 0, sizeof(footswitch));
	systime_t now;
	uint8_t but;
	switch_state state;
	uint8_t i;
	eventmask_t mask;
	thread_t * t;

	while (true)
	{
		mask = chEvtWaitAnyTimeout(
		EVENT_I2C_BUTTONS | EVENT_HARMONIZER_BUTTON | EVENT_TEST_BUTTON,MS2ST(100));

		if ((mask & EVENT_I2C_BUTTONS) || (mask & EVENT_HARMONIZER_BUTTON))
		{
			t = chMsgWait();
			buttons = chMsgGet(t);
			chMsgRelease(t, 0);
			if (!buttons)
			{
				but = footswitch.switchNumber;
				state = RELASED;
			}
			else
			{
				i = 0;
				if (mask & EVENT_I2C_BUTTONS)
				{
					while (!(buttons & 1))
					{
						buttons >>= 1;
						i++;
					}
					but = i;
				}
				else
				{
					but = 20;
				}
				state = PUSHED;
			}
		}
		else if (mask & EVENT_TEST_BUTTON)
		{
			but = 30;
			state = palReadPad(HARM_PORT, HARM_PIN);
		}

		if (mask)
		{
			footswitch.ms = ST2MS(chVTGetSystemTime()) - now;
			footswitch.switchNumberOld = footswitch.switchNumber;
			footswitch.stateOld = footswitch.state;
			footswitch.state = state;
			footswitch.switchNumber = but;
			now = ST2MS(chVTGetSystemTime());

			picoc_run_picoc_auto_thread(&footswitch);
		}
	}

	return 0;
}

void harm_interrupt(EXTDriver *extp, expchannel_t channel)
{
	chSysLockFromISR();
	chEvtSignalI(thd, EVENT_TEST_BUTTON);
	chSysUnlockFromISR();
}


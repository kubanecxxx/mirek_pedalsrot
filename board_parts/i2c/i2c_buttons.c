/**
 * @file i2c_buttons.c
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "i2c_master.h"
#include "i2c_buttons.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PCA_BUTTONS_ADDRESS 	0b0100010
#define BUTTON_EVENT_ID 		4

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static I2CDriver * i2c;

static THD_WORKING_AREA(buttons, 256);
static thread_t * foot_thd;
static thread_t * consum_thd;
static uint8_t thd_flag;

/* Private function prototypes -----------------------------------------------*/
static msg_t i2c_receive_thread(void * data);
static uint8_t reorder(uint8_t data);

/* Private functions ---------------------------------------------------------*/

void i2c_buttons_init(I2CDriver * i2cd)
{
	i2c = i2cd;

	uint8_t txbuf[2];
	txbuf[0] = PCA_DDR;
	txbuf[1] = 0xFF; //input
	i2cAcquireBus(i2c);
	i2cMasterTransmitTimeout(i2c, PCA_BUTTONS_ADDRESS, txbuf, 2, NULL, 0,
	TIME_INFINITE);
	txbuf[0] = PCA_POL;
	txbuf[1] = 0xFF; //inverse input polarity
	i2cMasterTransmitTimeout(i2c, PCA_BUTTONS_ADDRESS, txbuf, 2, NULL, 0,
	TIME_INFINITE);
	i2cReleaseBus(i2c);

	foot_thd = chThdCreateStatic(&buttons, sizeof(buttons), HIGHPRIO,
			i2c_receive_thread,
			NULL);
}

void i2c_buttons_cons_thread(thread_t *thd, uint8_t flag)
{
	consum_thd = thd;
	thd_flag = flag;
}

static virtual_timer_t vt2;
static EXTDriver * d;

/**
 * @brief thread for reading button inputs
 */
msg_t i2c_receive_thread(void * data)
{
	(void) data;
	chRegSetThreadName("i2c buttons");
	uint8_t txbuf = PCA_IDR;
	uint8_t rxbuf[2];
	uint8_t temp;
	uint8_t input_old = 0;
	static uint32_t brodcasty = 0;

	eventmask_t mask;
	while (TRUE)
	{
#if 0
		//čeká na přerušení
		mask = chEvtWaitOneTimeout(BUTTON_EVENT_ID, MS2ST(1000));

		if (mask)
#endif
		{
			i2cAcquireBus(i2c);
			i2cMasterTransmit(i2c, PCA_BUTTONS_ADDRESS, &txbuf, 1, rxbuf, 2);
			i2cReleaseBus(i2c);

			//if any changes then send message
			temp = reorder(rxbuf[0]);
			if (input_old != temp)
			{
				input_old = temp;
				if (consum_thd)
				{
					chEvtSignal(consum_thd, thd_flag);
					chMsgSend(consum_thd, temp);
				}
				brodcasty++;
			}
		}
		chThdSleepMilliseconds(50);
#if 0
		chSysLock();
		if (!chVTIsArmedI(&vt2))
		{
			extChannelEnableI(d, 15);
		}
		chSysUnlock();
#endif
	}
	return 0;
}

static void glitch(void * data)
{

	chSysLockFromISR();
	extChannelEnableI(data, 15);
	chSysUnlockFromISR();

}

uint8_t reorder(uint8_t data)
{
	uint8_t temp = 0;
	//bit swap - wrong soldering ...
	temp |= (data & 0b00100000) << 1;
	temp |= (data & 0b01000000) >> 6;
	temp |= (data & 0b00000001) << 2;
	temp |= (data & 0b00000010) << 2;
	temp |= (data & 0b00000100) << 2;
	temp |= (data & 0b00001000) << 2;
	temp |= (data & 0b10000000) >> 6;
	temp |= (data & 0b00010000) << 3;

	return temp;
}

/**
 * @brief external interrupt from PCA_BUTTONS
 * @notapi
 */
void foot_buttons_interrupt(EXTDriver *extp, expchannel_t channel)
{

	d = extp;
	chSysLockFromISR();
	extChannelDisableI(extp, channel);
	//if (!chVTIsArmedI(&vt2))
	//	chVTSetI(&vt2, MS2ST(20), (vtfunc_t) glitch, extp);

	//chDbgAssert(foot_thd, "thd is not defined");
	chEvtSignalI(foot_thd, BUTTON_EVENT_ID);
	chSysUnlockFromISR();
}

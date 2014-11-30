/**
 * @file delay.c
 * @author kubanec
 * @date 16.8.2012
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include <I2c_delay.h>
#include "rs232.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
 * I2C address set for delay DD3 - PCA9530 + DS18030
 */
///@brief I2C adresa PCA v delay
#define DELAY_PCA 0b1100001 //Harmnoist PCA 7-bit address
///@brief I2C adresa Dalas potenciometru
#define DELAY_DAL 0b0101000 //DAC 7-bit address MCP4728
/*
 * PCA registers
 */
///@brief PCA input data registr
#define PCA_INPUT_REG 0
#define PCA_PSC0 1
#define PCA_PWM0 2
#define PCA_PSC1 3
#define PCA_PWM1 4
#define PCA_LS0  5

///@brief PCA auto address increment flag
#define PCA_INCREMENT 0b00010000

/*
 * DALAS registers
 */
///@brief registr potenciometru na delay time
#define DAL_POTTIME 0b10101001
///@brief registr potenciomteru na volume
#define DAL_POTVOLUME 0b10101010
///@brief registr obou potenciometrů zajednou
#define DAL_POT_BOTH 0b10101111

/**
 * @addtogroup Delay
 * @{
 */

#ifdef I2C_DD3
static I2CDriver * i2c;

/**
 * @brief turn delay on/off - internal function shouldn't be used by user
 * @notapi
 * @param data 0/1
 */
void delay_init(I2CDriver * i2cd)
{
	i2c = i2cd;
}

void delay_onOff(uint8_t data)
{
	uint8_t txbuf[2];

	txbuf[0] = PCA_LS0;
	txbuf[1] = data ^ 1;
	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, DELAY_PCA, txbuf, 2, NULL, 0);
	i2cReleaseBus(i2c);
}

void delay_toggle(void)
{
	uint8_t a = delay_get();
	a ^= 1;
	delay_onOff(a);
}

/**
 * @brief vyčte jesli je DD3 zapnuty nebo vypnuty
 */
uint8_t delay_get(void)
{
	uint8_t txbuf[2];
	uint8_t rxbuf[2];

	txbuf[0] = PCA_INPUT_REG;

	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, DELAY_PCA, txbuf, 1, rxbuf, 2);
	i2cReleaseBus(i2c);

	return ((rxbuf[0] ) & 1);

}

/**
 * @brief nastaví poťák
 * @notapi
 * @param[in] kterej poťák
 * @param[in] nastavení jezdce potenciometru
 */
#if 0
void _delay_dalas(uint8_t channel, uint8_t value)
{
	uint8_t txbuf[2];
	eff_loop_t prev;

	if (channel == DAL_POTVOLUME && serial_getLoopState() == eff_loop_enabled)
	{
		prev = eff_loop_enabled;
		serial_loopBypass_delay();
		chThdSleepMilliseconds(100);
	}
	else
	{
		prev = eff_loop_bypass;
	}

	txbuf[0] = channel;
	txbuf[1] = value;
	i2cAcquireBus(&I2CD1);
	i2cMasterTransmit(&I2CD1, DELAY_DAL, txbuf, 2, NULL, 0);
	i2cReleaseBus(&I2CD1);

	if (prev == eff_loop_enabled && channel == DAL_POTVOLUME)
	{
		chThdSleepMilliseconds(150);
		serial_loopOn_delay();
	}
}
#endif

/**
 * @}
 */

#endif

/**
 * @file i2c_leds.c
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "i2c_master.h"
#include "i2c_leds.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PCA_LED_1_ADDRESS 		0b0100000
#define PCA_LED_2_ADDRESS 		0b0100001

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static I2CDriver * i2c;

static const uint8_t colors[] =
{ PCA_LED_1_ADDRESS, PCA_LED_2_ADDRESS };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void i2c_leds_init(I2CDriver * i2cd)
{
	i2c = i2cd;

	uint8_t txbuf[2];
	txbuf[0] = PCA_DDR;
	txbuf[1] = PCA_OUTPUT;

	i2cAcquireBus(i2c);
	i2cMasterTransmitTimeout(i2c, PCA_LED_1_ADDRESS, txbuf, 2, NULL, 0,
	TIME_INFINITE);
	i2cMasterTransmitTimeout(i2c, PCA_LED_2_ADDRESS, txbuf, 2, NULL, 0,
	TIME_INFINITE);
	i2cReleaseBus(i2c);
}

//bit swap because wrong soldering...
static uint8_t reorder(uint8_t in)
{
	uint8_t temp = in;
	temp &= 0x0F;
	temp |= ((in & 0b10000000) >> 1);
	temp |= ((in & 0b01000000) << 1);
	temp |= ((in & 0b00100000) >> 1);
	temp |= ((in & 0b00010000) << 1);

	return temp;
}

uint8_t i2c_leds_trasmit_receive(led_color_t color, uint8_t led_mask,
		led_code_t code)
{
	if (!IS_COLOR_OK(color))
		return 0;

	if (!IS_CODE_OK(code))
		return 0;

	uint8_t addr = colors[color];

	//read modify write
	uint8_t txbuf[2];
	uint8_t rxbuf[2];
	txbuf[0] = PCA_IDR;

	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, addr, txbuf, 1, rxbuf, 2);
	i2cReleaseBus(i2c);

	txbuf[0] = PCA_ODR;
	txbuf[1] = reorder(rxbuf[0]);
	led_mask = reorder(led_mask);

	if (code == ON)
	{
		txbuf[1] |= led_mask;
	}
	else if (code == OFF)
	{
		txbuf[1] &= ~(led_mask);
	}
	else if (code == TOGGLE)
	{
		txbuf[1] ^= led_mask;
	}
	else if (code == GET)
	{
		return (txbuf[1]);
	}
	else
	{
		return 0;
	}

	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, addr, txbuf, 2, NULL, 0);
	i2cReleaseBus(i2c);

	return 0;
}

/*
 void i2c_leds_enable(led_color_t color, uint8_t led)
 {

 }

 void i2c_leds_disable(led_color_t color, uint8_t led)
 {

 }

 void i2c_leds_toggle(led_color_t color, uint8_t led)
 {

 }

 bool i2c_leds_get(led_color_t color, uint8_t led)
 {

 }
 */

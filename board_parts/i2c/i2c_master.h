/**
 * @file i2c_user.h
 * @author kubanec
 * @date 9.8.2012
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef I2C_USER_H_
#define I2C_USER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "harmonist.h"
#include "delay.h"

/**
 * PCA register set
 */
#define PCA_IDR 	0
#define PCA_ODR		1
#define PCA_POL		2
#define PCA_DDR		3

/**
 * PCA port direction
 */
#define PCA_OUTPUT  0
#define PCA_INPUT	1

#include "i2c_leds.h"
#include "i2c_buttons.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define _BV(x) (1<<x)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void i2c_init(I2CDriver * i2c);
#ifdef I2C_TEST
void i2c_test(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* I2C_USER_H_ */

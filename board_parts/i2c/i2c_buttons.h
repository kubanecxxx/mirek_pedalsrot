/**
 * @file i2c_buttons.h
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BOARD_PARTS_I2C_I2C_BUTTONS_H_
#define BOARD_PARTS_I2C_I2C_BUTTONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void i2c_buttons_init(I2CDriver * i2cd);
void i2c_buttons_cons_thread(thread_t * thd,uint8_t flag);
void foot_buttons_interrupt(EXTDriver *extp, expchannel_t channel);


#define EXTERNAL_INTERRUPT_PCA  EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, foot_buttons_interrupt


#ifdef __cplusplus
}
#endif

#endif /* BOARD_PARTS_I2C_I2C_BUTTONS_H_ */

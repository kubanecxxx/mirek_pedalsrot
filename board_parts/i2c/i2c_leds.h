/**
 * @file i2c_leds.h
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BOARD_PARTS_I2C_I2C_LEDS_H_
#define BOARD_PARTS_I2C_I2C_LEDS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	GREEN = 0 , YELLOW = 1
} led_color_t;

typedef enum
{
	ON, OFF, TOGGLE, GET
} led_code_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define IS_COLOR_OK(color) (color == YELLOW || color == GREEN)
#define IS_CODE_OK(code)  (code <= GET)

/* Exported functions --------------------------------------------------------*/
void i2c_leds_init(I2CDriver * i2c);
uint8_t i2c_leds_trasmit_receive(led_color_t color, uint8_t led_mask,
		led_code_t code);
/*
 void i2c_leds_enable(led_color_t color, uint8_t led);
 void i2c_leds_disable(led_color_t color, uint8_t led);
 void i2c_leds_toggle(led_color_t color, uint8_t led);
 bool i2c_leds_get(led_color_t color, uint8_t led);
 */

#ifdef __cplusplus
}
#endif

#endif /* BOARD_PARTS_I2C_I2C_LEDS_H_ */

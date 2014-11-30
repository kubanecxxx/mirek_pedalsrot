/**
 * @file delay.h
 * @author kubanec
 * @date 16.8.2012
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DELAY_H_
#define DELAY_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup Delay
 * @ingroup I2C
 * @brief API pro nastavení delay DD3
 */

/**
 * @addtogroup Delay
 * @{
 */

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
uint8_t delay_get(void);
void delay_toggle(void);
void delay_onOff(uint8_t data);



#ifdef __cplusplus
}
#endif

#endif /* DELAY_H_ */

/**
 * @file led_mgt.h
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MANAGEMENT_LED_MGT_H_
#define MANAGEMENT_LED_MGT_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern struct LibraryFunction led_mgt_functions[];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void led_mgt_picoc_include(Picoc * pc);
void led_mgt_init(void);

#ifdef __cplusplus
}
#endif

#endif /* MANAGEMENT_LED_MGT_H_ */

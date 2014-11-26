/**
 * @file input_mgt.h
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MANAGEMENT_INPUT_MGT_H_
#define MANAGEMENT_INPUT_MGT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void input_mgt_init(void);
void harm_interrupt(EXTDriver *extp, expchannel_t channel);

#define EXTERNAL_INTERRUPT_HARMONIZER EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, harm_interrupt

#ifdef __cplusplus
}
#endif

#endif /* MANAGEMENT_INPUT_MGT_H_ */

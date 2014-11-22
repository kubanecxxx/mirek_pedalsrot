/**
 * @file rs232.h
 * @author kubanec
 * @date 18.8.2012
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RS232_H_
#define RS232_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "chprintf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern BaseSequentialStream * marshall;
extern const struct LibraryFunction rs232_picoc_table[];
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void serial_init(void);
void serialPicocIncludeInit(Picoc *pc);

#ifdef __cplusplus
}
#endif

#endif /* RS232_H_ */

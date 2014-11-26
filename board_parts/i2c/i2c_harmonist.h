/**
 * @file harmonist.h
 * @author kubanec
 * @date 10.8.2012
 *
 * @brief harmonist voltage constants
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HARMONIST_H_
#define HARMONIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup HARMONIST
 * @brief API pro ovládání harmonizéru po I2C
 * @ingroup I2C
 */

/**
 * @addtogroup HARMONIST
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <i2c_master.h>
#include "picoc.h"
/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @}
 */

void harm_init(I2CDriver * i2c);
void harm_set_cons_thread(thread_t * thd, eventmask_t event);

extern const struct LibraryFunction harm_libs[];

#ifdef __cplusplus
}
#endif

#endif /* HARMONIST_H_ */

/*
 * switch_master.h
 *
 *  Created on: 23.8.2012
 *      Author: kubanec
 */

#ifndef SWITCH_MASTER_H_
#define SWITCH_MASTER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************
 * Includes
 ********************************************************************/
#include "optocouplers.h"
#include "switch_lld.h"

/********************************************************************
 * Exported functions
 ********************************************************************/
extern const struct LibraryFunction gpio_picoc_table[];

void switch_masterGpioInit(void);
void switch_picoc_include_init(Picoc * pc);

#ifdef __cplusplus
}
#endif

#endif /* SWITCH_MASTER_H_ */

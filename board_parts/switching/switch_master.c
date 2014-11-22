/*
 * switch_master.c
 *
 *  Created on: 23.8.2012
 *      Author: kubanec
 */

/********************************************************************
 * Includes
 ********************************************************************/
#include "ch.h"
#include "hal.h"
#include "picoc.h"
#include "switch_master.h"

/********************************************************************
 * Private functions
 ********************************************************************/
static void enable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void disable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void toggle(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void get(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void disableAll(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);

const struct LibraryFunction gpio_picoc_table[] =
{
{ enable, "void eff_enable(int);" },
{ disable, "void eff_disable(int);" },
{ toggle, "void eff_toggle(int);" },
{ get, "int eff_get(int);" },
{ disableAll, "void eff_disable_all(void);" },
{ NULL, NULL } };

void switch_picoc_include_init(Picoc * pc)
{
	static const char conf[] =
	{ "#define DELAY 1 \n \
			 " };
	PicocParse(pc, "nofile", conf, strlen(conf), TRUE, TRUE, FALSE, FALSE);
}

/**
 * @defgroup Switching
 * @brief API pro ovládání efektů přes relé nebo po optočlenech
 */

/**
 * @brief init portů pro relé a optočleny
 * @ingroup Switching
 */
void switch_masterGpioInit(void)
{
	switch_init();
	opto_init();
}

static void enable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	int tmp = Param[0]->Val->Integer;

	//0-19 relays
	if (tmp < 20)
	{

		switch_setRelay((tmp));
	}
	//20 and more opto
	else if (tmp > 19)
	{
		opto_enableEffect((tmp - 20));
	}
}

static void disable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	int tmp = Param[0]->Val->Integer;

	//0-19 relays
	if (tmp < 20)
	{

		switch_clearRelay((tmp));
	}
	//20 and more opto
	else if (tmp > 19)
	{
		opto_disableEffect((tmp - 20));
	}
}

static void toggle(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	int tmp = Param[0]->Val->Integer;

	//0-19 relays
	if (tmp < 20)
	{

		switch_toggleRelay((tmp));
	}
	//20 and more opto
	else if (tmp > 19)
	{
		opto_toggleEffect((tmp - 20));
	}
}

static void get(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) NumArgs;

	int tmp = Param[0]->Val->Integer;

	//0-19 relays
	if (tmp < 20)
	{
		ReturnValue->Val->Integer = switch_getRelay(tmp);
		return;
	}
	//20 and more opto
	else if (tmp > 19)
	{
		ReturnValue->Val->Integer = opto_getEffect((tmp - 20));
		return;
	}
}

static void disableAll(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	switch_setRelays(0);
	opto_setEffects(0);
}

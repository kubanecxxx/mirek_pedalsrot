/**
 * @file led_mgt.c
 * @author kubanec
 * @date 23. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "picoc.h"
#include "i2c_leds.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static THD_WORKING_AREA(led_mgt_wa,256);
static uint8_t flash_mask[2];

/* Private function prototypes -----------------------------------------------*/
static void led_disable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void led_disable_mask(struct ParseState *Parser,
		struct Value *ReturnValue, struct Value **Param, int NumArgs);
static void led_enable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void led_flash(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void led_toggle(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void led_get(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void led_disable_all(struct ParseState *Parser,
		struct Value *ReturnValue, struct Value **Param, int NumArgs);

static msg_t led_mgt_thd(void * arg);
/* Private functions ---------------------------------------------------------*/

struct LibraryFunction led_mgt_functions[] =
{
{ led_disable, "void led_disable(int,int);" }, //0 color GREEN, 1 color YELLOW, led number
		{ led_enable, "void led_enable(int,int);" },
		{ led_flash, "void led_flash(int,int);" }, //0 color GREEN, 1 color YELLOW, led number
		{ led_toggle, "void led_toggle(int,int);" },
		{ led_get, "int led_get(int,int);" },
		{ led_disable_all, "void led_disable_all(void);" },
		{ led_disable_mask, "void led_disable_mask(int, int);" }, //color, mask
		{ NULL, NULL } };

void led_mgt_picoc_include(Picoc * pc)
{
	(void) pc;
}

void led_mgt_init(void)
{
	chThdCreateStatic(&led_mgt_wa, sizeof(led_mgt_wa), NORMALPRIO - 10,
			led_mgt_thd, NULL);
}

msg_t led_mgt_thd(void * arg)
{
	(void) arg;

	led_color_t i = 0;
	while (true)
	{
		chThdSleepMilliseconds(200);
		for (i = 0; i < 2; i++)
		{
			i2c_leds_trasmit_receive(i, flash_mask[i], TOGGLE);
		}
	}

	return 0;
}

void led_enable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;

	led_color_t color = Param[0]->Val->Integer;
	int num = Param[1]->Val->Integer;

	i2c_leds_trasmit_receive(color, 1 << num, ON);
}

void led_toggle(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;

	led_color_t color = Param[0]->Val->Integer;
	int num = Param[1]->Val->Integer;

	i2c_leds_trasmit_receive(color, 1 << num, TOGGLE);
}

void led_disable(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	led_color_t color = Param[0]->Val->Integer;
	int num = Param[1]->Val->Integer;

	if (IS_COLOR_OK(color))
		flash_mask[color] &= ~(1 << num);
	i2c_leds_trasmit_receive(color, 1 << num, OFF);
}

void led_disable_mask(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	led_color_t color = Param[0]->Val->Integer;
	int num = Param[1]->Val->Integer;

	if (IS_COLOR_OK(color))
		flash_mask[color] &= ~(num);
	i2c_leds_trasmit_receive(color, num, OFF);
}

void led_flash(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;

	led_color_t color = Param[0]->Val->Integer;
	int num = Param[1]->Val->Integer;

	if (IS_COLOR_OK(color))
	{
		flash_mask[color] |= 1 << num;
	}
}

static void led_get(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) NumArgs;

	led_color_t color = Param[0]->Val->Integer;
	int num = Param[1]->Val->Integer;

	uint8_t mask = i2c_leds_trasmit_receive(color, 1, GET);

	mask >>= num;
	mask &= 1;

	ReturnValue->Val->Integer = mask;
}

static void led_disable_all(struct ParseState *Parser,
		struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	flash_mask[YELLOW] = 0;
	flash_mask[GREEN] = 0;
	i2c_leds_trasmit_receive(YELLOW, 0xff, OFF);
	i2c_leds_trasmit_receive(GREEN, 0xff, OFF);
}

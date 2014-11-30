/**
 * @file rs232.c
 * @author kubanec
 * @date 18.8.2012
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "picoc.h"
#include "rs232.h"
#include "gui_api.h"

/**
 * @defgroup RS232
 *
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 * @brief stream pro posilání dat do maršála
 * @notapi
 * @ingroup RS232
 */

BaseSequentialStream * marshall = (BaseSequentialStream*) &SD2;
static uint8_t mute_memory;
static uint8_t loop_memory;

/* Private function prototypes -----------------------------------------------*/

static void volume(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void gain(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void sensitivity(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void mute(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void loop(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void get_loop(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void get_mute(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
static void set_text(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
/* Private functions ---------------------------------------------------------*/

const struct LibraryFunction rs232_picoc_table[] =
{
{ volume, "void mar_volume(int);" }, //volume 1-4
		{ gain, "void mar_gain(int);" }, //gain 1-4
		{ sensitivity, "void mar_sensitivity(int);" }, //1 high , 0 low sens
		{ mute, "void mar_muting(int);" }, //1 mute, 0 unmute
		{ loop, "void mar_loop(int);" }, //1 loop enabled, 0 loop bypassed
		{ get_loop, "void mar_get_loop(int);" }, //1 loop enabled, 0 loop bypassed
		{ get_mute, "void mar_get_mute(int);" }, //1 muted, 0 not muted
		{ set_text, "void set_text(char *);" }, //text
		{ NULL, NULL } };

void serialPicocIncludeInit(Picoc * pc)
{
	/*
	 static const char conf[] =
	 {
	 "#define mar_lowsens mar_sensitivity(0) \n \
		#define mar_highsens mar_sensitivity(1) \n\
	    #define mar_mute mar_muting(1) \n \
		#define mar_unmute mar_muting(0) \n\
		#define mar_enableloop mar_loop(1)\n\
		#define mar_disableloop mar_loop(0) " };
	 PicocParse(pc, "nofile", conf, strlen(conf), TRUE, TRUE, FALSE, FALSE);
	 */
}

/**
 * @brief nastavení UARTU
 * @notapi
 * @ingroup RS232
 */
static const SerialConfig cfg =
{ 9600, 0, 0, 0 };

/**
 * @brief inicializace UART2
 * @ingroup RS232
 */
void serial_init(void)
{
	sdStart(&SD2, &cfg);
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
}

void volume(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	uint8_t channel = Param[0]->Val->Integer;

	if (channel != 0)
	{
		chprintf(marshall, "volume %d\r\n\r\n", channel);
		gui_api.volume = channel ;
		//_marshall_state.volume = channel;
	}
}

void gain(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	uint8_t tmp = Param[0]->Val->Integer;

	if (tmp != 0)
	{
		chprintf(marshall, "gain %d\r\n\r\n", tmp);
		gui_api.gain = tmp ;
	}
}
void sensitivity(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	uint8_t tmp = Param[0]->Val->Integer;

	if (tmp == 0)
	{
		chprintf(marshall, "channel low\r\n\r\n");
		gui_api.highSensitivity = 0;
	}
	else if (tmp == 1)
	{
		gui_api.highSensitivity = 1;
		chprintf(marshall, "channel high\r\n\r\n");
	}
}

void get_mute(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) Param;
	(void) NumArgs;
	ReturnValue->Val->Integer = mute_memory;
}

void mute(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	uint8_t tmp = Param[0]->Val->Integer;

	if (tmp == 0)
	{
		chprintf(marshall, "mute off\r\n\r\n");
		mute_memory = 0;
		gui_api.muteEnabled = 0;
	}
	else if (tmp == 1)
	{
		chprintf(marshall, "mute on\r\n\r\n");
		mute_memory = 1;
		gui_api.muteEnabled = 1;
	}
}

void get_loop(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) Param;
	(void) NumArgs;

	ReturnValue->Val->Integer = loop_memory;
}

void loop(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	uint8_t tmp = Param[0]->Val->Integer;

	if (tmp == 0)
	{
		chprintf(marshall, "loop off\r\n\r\n");
		loop_memory = 0;
		gui_api.loopEnabled = 0;
	}
	else if (tmp == 1)
	{
		chprintf(marshall, "loop on\r\n\r\n");
		loop_memory = 1;
		gui_api.loopEnabled = 1;
	}
}

void set_text(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	static char text[20];
	char * p;

	p = Param[0]->Val->Pointer;
	strcpy(text,p);
	gui_api.text = text;
	gui_api.text_dirty = 1;
}

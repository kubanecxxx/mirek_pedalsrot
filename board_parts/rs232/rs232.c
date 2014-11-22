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
/* Private functions ---------------------------------------------------------*/

const struct LibraryFunction rs232_picoc_table[] =
{
{ volume, "void mar_volume(int);" }, //volume 1-4
		{ gain, "void mar_gain(int);" }, //gain 1-4
		{ sensitivity, "void mar_sensitivity(int);" }, //1 high , 0 low sens
		{ mute, "void mar_muting(int);" }, //1 mute, 0 unmute
		{ loop, "void mar_loop(int);" }, //1 loop enabled, 0 loop bypassed
		{ NULL, NULL } };

void serialPicocIncludeInit(Picoc * pc)
{
	static const char conf[] =
	{ "#define mar_lowsens mar_sensitivity(0) \n \
		#define mar_highsens mar_sensitivity(1) \n\
	    #define mar_mute mar_muting(1) \n \
		#define mar_unmute mar_muting(0) \n\
		#define mar_enableloop mar_loop(1)\n\
		#define mar_disableloop mar_loop(0) "};
	PicocParse(pc, "nofile", conf, strlen(conf), TRUE, TRUE, FALSE, FALSE);

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
	}
	else if (tmp == 1)
	{
		chprintf(marshall, "channel high\r\n\r\n");
	}
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
	}
	else if (tmp == 1)
	{
		chprintf(marshall, "mute on\r\n\r\n");
	}
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
	}
	else if (tmp == 1)
	{
		chprintf(marshall, "loop on\r\n\r\n");
	}
}

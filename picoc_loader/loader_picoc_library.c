/**
 * @file loader_picoc_library.c
 * @author kubanec
 * @date 21. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "picoc.h"
#include "stm32f4xx_flash.h"
#include "picoc_threads.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern void ram_enable(bool en);
uint8_t * flash_base = (uint8_t *) (FLASH_BASE + ((1024 - 128) * 1024));
static const uint8_t sector = FLASH_Sector_11;

static int flashWrite(uint32_t * Address, void * datas, uint32_t size)
{
	uint32_t * data = (uint32_t *) datas;
	uint32_t t = (uint32_t) Address;

	FLASH_Unlock();
	while (size % 4 != 0)
		size++;

	size /= 4;

	while (size--)
	{
		if (FLASH_ProgramWord(t, *(data++)) == FLASH_COMPLETE)
		{
			t += 4;
		}
		else
		{
			FLASH_Lock();
			return -1;
		}
	}
	FLASH_Lock();

	return 0;
}

static int flashErase(uint32_t sector)
{
	FLASH_Unlock();
	FLASH_ClearFlag(
			FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR
					| FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
	 be done by word */
	if (FLASH_EraseSector(sector, VoltageRange_3) != FLASH_COMPLETE)
	{
		FLASH_Lock();
		return -1;
	}
	FLASH_Lock();

	return 0;
}

extern char script_buffer[1024 * 32];
static void secret_function(struct ParseState *Parser,
		struct Value *ReturnValue, struct Value **Param, int NumArgs)
{

	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;
	char * p = script_buffer;
	size_t counter = 0;

//self while loop with reading lines.... until another secret sequence or eof
	PlatformPrintf(Parser->pc,
			"disabling shell and starting write raw data to buffer\n");
	char c = PlatformGetCharacter(Parser->pc);

	while ((c != 0x3) && (c != 0x1a))
	{
		*p = c;
		p++;
		counter++;
		c = PlatformGetCharacter(Parser->pc);
	}
	*p = 0;

	PlatformPrintf(Parser->pc, "memory usage: %d percent (%d of %d bytes)\n",
			counter / sizeof(script_buffer), counter, sizeof(script_buffer));
	PlatformPrintf(Parser->pc, "data reading finished, returning to shell\n");

}

static void read_flash(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	PlatformPrintf(Parser->pc, "%s", flash_base);
}

static void use_ram(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	ram_enable(true);
	PlatformPrintf(Parser->pc, "switched to ram");

}

static void use_flash(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	ram_enable(false);
	PlatformPrintf(Parser->pc, "switched to flash");

}

static void read_ram(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	PlatformPrintf(Parser->pc, "%s", script_buffer);
}

static void ram_to_rom(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Param;

	//delete flash page
	PlatformPrintf(Parser->pc, "erasing flash\n");
	if (!flashErase(sector))
	{
		//write data to flash
		PlatformPrintf(Parser->pc, "writing to flash\n");
		if (!flashWrite((uint32_t *) flash_base, script_buffer,
				strlen(script_buffer) + 1))
		{
			PlatformPrintf(Parser->pc, "done!\n");
		}
		else
		{
			PlatformPrintf(Parser->pc, "!! writing error !!\n");
		}
	}
	else
	{
		PlatformPrintf(Parser->pc, "!! flash erasing error !!\n");
	}

}

static void stimulate(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Parser;

	footswitch_picoc_data_t d;
	d.state = Param[1]->Val->Integer;
	d.stateOld = Param[3]->Val->Integer;
	d.switchNumber = Param[0]->Val->Integer;
	d.switchNumberOld = Param[2]->Val->Integer;
	d.ms = Param[4]->Val->Integer;

	picoc_run_picoc_auto_thread(&d);
}

static void terminate(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Parser;
	(void) Param;

	picoc_threads_terminate_auto_thread();
}


/* list of all library functions and their prototypes */
struct LibraryFunction loaderFunctions[] =
{
{ secret_function, "void super_secret_function();" },
{ read_ram, "void read_ram();" },
{ read_flash, "void read_flash();" },
{ use_flash, "void use_flash();" },
{ use_ram, "void use_ram();" },
{ ram_to_rom, "void ram_to_rom();" },
{ stimulate, "void stimulate(int, int , int ,int,int);" }, //button, state, button old, state old, time
{ terminate, "void terminate();" },
{ NULL, NULL } };

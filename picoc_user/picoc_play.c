/* picoc main program - this varies depending on your operating system and
 * how you're using picoc */

/* include only picoc.h here - should be able to use it with only the external interfaces, no internals from interpreter.h */
#include "picoc.h"
#include "picoc_threads.h"
#include "kchsprintf.h"
#include "rs232.h"
#include "switch_master.h"
#include "led_mgt.h"
#include "i2c_harmonist.h"

extern const Picoc_Callbacks pc_cb;
extern const Picoc_IO pc_io;

extern struct LibraryFunction BasicFunctions[];
extern struct LibraryFunction loaderFunctions[];

static const Picoc_User_Library_Table libs[] =
{
{ "basic.h", NULL, NULL, BasicFunctions },
{ "loader.h", NULL, NULL, loaderFunctions },
{ "marshall.h", serialPicocIncludeInit, NULL, rs232_picoc_table },
{ "outputs.h", switch_picoc_include_init, NULL, gpio_picoc_table },
{ "leds.h", led_mgt_picoc_include, NULL, led_mgt_functions },
{ "harmonist.h", NULL, NULL, harm_libs },
{ NULL, NULL, NULL, NULL } };

static const Picoc_User_Config auto_cfg =
{ (uint8_t *) 0x10000000, 1024 * 48, &pc_io, &pc_cb, libs };

static const Picoc_User_Config interactive_cfg =
{ (uint8_t *) 0x10000000 + 48 * 1024, 1024 * 16, &pc_io, &pc_cb, libs };

extern uint8_t debug_enabled;

/* platform-dependent code for running programs is in this file */
int picoc(const char *SourceStr, const footswitch_picoc_data_t * foot)
{
	static Picoc pc;
	char variables[100];
	systime_t t;

	if (!SourceStr || !SourceStr[0])
		return 1;

	PicocInitialise(&pc, &auto_cfg);
	pc.name = (const char *) "auto";

	/*
	for (pos = SourceStr; *pos != 0; pos++)
	{
		if (*pos == 0x1a)
		{
			*pos = 0x20;
		}
	}
	*/


	if (debug_enabled)
	{
		PlatformPrintf(&pc, "-----start-----\n");
		t = chVTGetSystemTime();
	}

	PicocIncludeAllSystemHeaders(&pc);

	if (foot)
	{
		chsprintf(variables,
				"int button = %d;\n int button_old = %d;\n int ms = %d;\n int state = %d;\n int state_old = %d;\n",
				foot->switchNumber, foot->switchNumberOld, foot->ms,
				foot->state, foot->stateOld);
		PicocParse(&pc, "nofile", variables, strlen(variables), TRUE, TRUE,
		FALSE, FALSE);

		if (debug_enabled)
			PlatformPrintf(&pc, variables);
	}

	PicocParse(&pc, "nofile", SourceStr, strlen(SourceStr), TRUE, TRUE,
	FALSE, FALSE);

	if (debug_enabled)
	{
		PlatformPrintf(&pc, "------stop---%d ms-\n", chVTGetSystemTime() - t);

	}
	PicocCleanup(&pc);

	return 0;
}

int picoc_interactive(void)
{
	static Picoc pc;

	PicocInitialise(&pc, &interactive_cfg);
	pc.name = (const char *) "interactive";
	PicocIncludeAllSystemHeaders(&pc);
	PicocParseInteractive(&pc);
	PicocCleanup(&pc);

	return 0;
}


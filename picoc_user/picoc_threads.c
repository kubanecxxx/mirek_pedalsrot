/**
 * @file picoc_thread.c
 * @author kubanec
 * @date 21. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "picoc_threads.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define THD_SIZE 	16*1024
static THD_WORKING_AREA(picoc_wa, THD_SIZE);
static THD_WORKING_AREA(picoc_waa, THD_SIZE);
static thread_t * pico_auto;
static thread_t * pico_interactive;

static bool ram = 0;

extern uint8_t * flash_base;
char script_buffer[1024 * 32];

/* Private function prototypes -----------------------------------------------*/
extern int picoc(char *SourceStr, const footswitch_picoc_data_t * foot);
extern int picoc_interactive(void);

/* Private functions ---------------------------------------------------------*/

void ram_enable(bool en)
{
	ram = en;
}

static msg_t pcb(void *foot)
{

	chRegSetThreadName("picoc auto");
	char * p = NULL;
	if (ram)
		p = script_buffer;
	else
		p = (char *) flash_base;
	picoc(p, foot);

	return 0;
}

static msg_t pcb2(void *a)
{
	(void) a;
	chRegSetThreadName("picoc interactive");
	picoc_interactive();

	return 0;
}

void picoc_threads_init(void)
{
	pico_auto = chThdCreateStatic(&picoc_wa, sizeof(picoc_wa),
	NORMALPRIO, &pcb,
	NULL);
	pico_interactive = chThdCreateStatic(&picoc_waa, sizeof(picoc_waa), NORMALPRIO,
			&pcb2,
			NULL);
}

void picoc_threads_loop(void)
{
	bool term;
	chSysLock();
	term = chThdTerminatedX(pico_interactive);
	chSysUnlock();
	if (term)
	{
		pico_interactive = chThdCreateStatic(&picoc_waa, sizeof(picoc_waa), NORMALPRIO,
				&pcb2,
				NULL);
	}
}

void picoc_threads_terminate_auto_thread(void)
{
	chThdTerminate(pico_auto);
}

void picoc_run_picoc_auto_thread(const footswitch_picoc_data_t * foot)
{
	static footswitch_picoc_data_t d;
	bool term;
	chSysLock();
	term = chThdTerminatedX(pico_auto);
	chSysUnlock();

	if (term)
	{
		memcpy(&d, foot, sizeof(d));
		pico_auto = chThdCreateStatic(&picoc_wa, sizeof(picoc_wa), NORMALPRIO, &pcb,
				(void*) &d);
	}
}


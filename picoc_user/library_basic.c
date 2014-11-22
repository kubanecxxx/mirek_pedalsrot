#include "interpreter.h"
#include "ch.h"
#include "hal.h"

static void test(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) Parser;
	(void) ReturnValue;
	//uint8_t a = Param[0]->Val->UnsignedCharacter;
	palWritePad(GPIOD, 13, Param[0]->Val->Integer);
}

static void wait(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) Parser;
	(void) ReturnValue;
	chThdSleepMilliseconds(Param[0]->Val->Integer);
}

static uint8_t _data[256];
static void pif_save_data(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) Parser;
	(void) ReturnValue;
	size_t idx = Param[0]->Val->UnsignedCharacter;
	uint8_t data = Param[1]->Val->UnsignedCharacter;

	if (idx < sizeof(_data))
		_data[idx] = data;
}

static void pif_load_data(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) Parser;
	uint8_t idx = Param[0]->Val->UnsignedCharacter;
	ReturnValue->Val->UnsignedCharacter = _data[idx];
}

static void pif_free_mem(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) ReturnValue;
	(void) Param;

	size_t mem = Parser->pc->HeapBottom - Parser->pc->HeapStackTop;
	PlatformPrintf(Parser->pc, "free picoc memory %d", mem);
}

static void pif_printf_mem(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) ReturnValue;
	(void) Param;

	union AnyValue v;
	memcpy(&v, Param[1]->Val, sizeof(v));

	if (NumArgs == 1)
		PlatformPrintf(Parser->pc, Param[0]->Val->Pointer);
	else if (NumArgs == 2)
		PlatformPrintf(Parser->pc, Param[0]->Val->Pointer,
				Param[1]->Val->Integer);
	else if (NumArgs == 3)
		PlatformPrintf(Parser->pc, Param[0]->Val->Pointer,
				Param[1]->Val->Integer, Param[2]->Val->Integer);
}

static void pif_print_mem(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) NumArgs;
	(void) ReturnValue;
	(void) Param;

	if (NumArgs == 1)
		PlatformPrintf(Parser->pc, "%d", Param[0]->Val->Integer);
}

static void pif_threads(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) Param;
	(void) NumArgs;
	static const char *states[] =
	{ CH_STATE_NAMES };
	thread_t *tp;
	int i = 0;

	PlatformPrintf(Parser->pc,
			"num name    addr    stack prio refs     state time\r\n");
	tp = chRegFirstThread();
	do
	{
		PlatformPrintf(Parser->pc, "%d %s %08lx %08lx %4lu %4lu %9s\r\n", i++,
				tp->p_name, (uint32_t ) tp, (uint32_t ) tp->p_ctx.r13,
				(uint32_t ) tp->p_prio, (uint32_t ) (tp->p_refs - 1),
				states[tp->p_state]);
		tp = chRegNextThread(tp);
	} while (tp != NULL);
}

extern uint8_t debug_enabled;
static void pif_debug_enable(struct ParseState *Parser,
		struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Parser;

	debug_enabled = Param[0]->Val->Integer;
}

static void shouldExit(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) ReturnValue;
	(void) NumArgs;
	(void) Parser;
	(void) Param;

	if (chThdShouldTerminateX())
		chThdExit(0);
}

/* list of all library functions and their prototypes */
struct LibraryFunction BasicFunctions[] =
{
{ test, "void test(int);" }, //
		{ wait, "void wait(int);" }, //ms
		{ pif_save_data, "void save_data(unsigned char, unsigned char);" }, //idx, data
		{ pif_load_data, "unsigned char load_data(unsigned char);" }, //idx
		{ pif_free_mem, "void memory(void);" },
		{ pif_printf_mem, "void printf(char * , int);" },
		{ pif_print_mem, "void print( int);" },
		{ pif_threads, "void threads(void);" },
		{ pif_debug_enable, "void debug(int);" }, //0 disable, 1 enable debug
		{ shouldExit, "void should_exit(void);" },
		{ NULL, NULL } };


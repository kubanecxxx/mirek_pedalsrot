/**
 * @file harmonist.c
 * @author kubanec
 * @date 10.8.2012
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <i2c_harmonist.h>
#include "ch.h"
#include "hal.h"
#include "picoc.h"
#include "rs232.h"
#include "gui_api.h"

/**
 * @addtogroup HARMONIST
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *  @brief I2C address set for harmonizer - PCA9536
 */
#define HARM_PCA 0b1000001 //Harmnoist PCA 7-bit address

/**
 * @brief počet poloh MODE
 */
#define HARM_MODE_COUNT 5

///@brief Počet poloh KEY
#define HARM_KEY_COUNT 12
///@brief Počet poloh SHIFT
#define HARM_SHIFT_COUNT 11

/**
 * @brief  I2C address for DAC MCP4728
 */
#define DACAN 0b1100000 //DAC 7-bit address MCP4728
/**
 * @brief referenčí napětí DAC
 */
#define Vref 3.3
/**
 * @brief output voltage to bits DAC MCP4728
 * @param[in] chtěné výstupní napětí ve floatu
 */
#define DAC_VOLTAGE(Vout) ((uint16_t)(Vout*4096/Vref))

/**
 * @brief MODE konstanty pro D/A převodnik
 */
typedef union
{
	struct
	{
		uint16_t MAJOR;
		uint16_t MINOR;
		uint16_t PITCH_SHIFT;
		uint16_t DETUNE;
		uint16_t SBEND;
	} s;
	uint16_t a[HARM_MODE_COUNT];
} harmonizer_mode_t;

/**
 * @brief KEY konstanty pro D/A převodnik
 */
typedef union
{
	struct
	{
		uint16_t C;
		uint16_t Cx;
		uint16_t D;
		uint16_t Eb;
		uint16_t E;
		uint16_t F;
		uint16_t Fx;
		uint16_t G;
		uint16_t Gx;
		uint16_t A;
		uint16_t Ax;
		uint16_t H;
	} s;
	uint16_t a[HARM_KEY_COUNT];
} harmonizer_key_t;

/**
 * @brief HARMONY konstanty pro D/A převodnik
 */
typedef union
{
	uint16_t a[HARM_SHIFT_COUNT];
} harmonizer_harmony_t;

/**
 * @brief sada všech konstant
 */
typedef struct harmonizer_t
{
	harmonizer_mode_t MODE;
	harmonizer_key_t KEY;
	harmonizer_harmony_t HARMONY;
} harmonizer_t;

/* Exported constants --------------------------------------------------------*/
/**
 * @brief DAC channels
 */
typedef enum
{
	CHAN_MODE = 0, CHAN_VOLUME = 1, CHAN_KEY = 2, CHAN_HARM = 3
} DAC_channel;

/**
 * @brief HARMONIST PCA PINS
 */
typedef enum
{
	HARM_LDAC = 0, HARM_EFF = 1, HARM_BUT = 2, HARM_LED = 3
} HARM_pins;

/* Private macro -------------------------------------------------------------*/
/*
 * DAC channels
 */
///@brief nastavení hlasitosi harmonizéru
#define harm_volume(vol)  _dac_write(CHAN_VOLUME,vol)
///@brief výběr módu harmonizéru
#define harm_mode(x)  _dac_write(CHAN_MODE,HARMONIZER.MODE.a[x])
///@brief výběr key
#define harm_key(x)   _dac_write(CHAN_KEY,HARMONIZER.KEY.a[x])
///@brief výběr harmony
#define harm_harmony(x) _dac_write(CHAN_HARM,HARMONIZER.HARMONY.a[x])

///@brief PCA input LDAC
#define harm_getInput_LDAC(inputs) ((inputs >> HARM_LDAC) & 1)
///@brief PCA input EFF
#define harm_getInput_EFF(inputs) ((inputs >> HARM_EFF) & 1)
///@brief PCA input BUT
#define harm_getInput_BUT(inputs) (!((inputs >> HARM_BUT) & 1))
///@brief PCA input LED
#define harm_getInput_LED(inputs) ((inputs >> HARM_LED) & 1)

/*
 * PCA outputs
 */
#define harm_releaseButton(inputs) _harm_SetOutputs(inputs | _BV(HARM_EFF))
#define harm_pushButton(inputs) _harm_SetOutputs(inputs & (~_BV(HARM_EFF)))
#define harm_setLDAC(inputs) _harm_SetOutputs(inputs | _BV(HARM_LDAC))

#define harm_enable() _harm_enabled = TRUE
#define harm_disable() _harm_enabled = FALSE
#define harm_toggle() _harm_enabled = !_harm_enabled

/* Private variables ---------------------------------------------------------*/
static THD_WORKING_AREA(wa_harmonizer,256);
bool _harm_enabled;
static I2CDriver * i2c;
static thread_t * consumer_thd;
static eventmask_t evt_mask;

//extern logic_active_t active;

///@brief sada konstant pro DAC
const harmonizer_t HARMONIZER =
{
/*
 * MODEs
 */
{ DAC_VOLTAGE(0), DAC_VOLTAGE(0.151), DAC_VOLTAGE(0.494), DAC_VOLTAGE(0.839),
		DAC_VOLTAGE(1.201) },
/*
 * KEY
 */
{ DAC_VOLTAGE(0), DAC_VOLTAGE(0.181), DAC_VOLTAGE(0.493), DAC_VOLTAGE(0.810),
		DAC_VOLTAGE(1.129), DAC_VOLTAGE(1.462), DAC_VOLTAGE(1.810), DAC_VOLTAGE(
				2.141), DAC_VOLTAGE(2.464), DAC_VOLTAGE(2.815), DAC_VOLTAGE(
				3.104), DAC_VOLTAGE(3.288) },
/*
 * HARMONY
 */
{ DAC_VOLTAGE(0), DAC_VOLTAGE(0.205), DAC_VOLTAGE(0.558), DAC_VOLTAGE(0.867),
		DAC_VOLTAGE(1.254), DAC_VOLTAGE(1.661), DAC_VOLTAGE(2.041), DAC_VOLTAGE(
				2.436), DAC_VOLTAGE(2.815), DAC_VOLTAGE(3.132), DAC_VOLTAGE(
				3.228) } };
/* Private function prototypes -----------------------------------------------*/
static void harm_thread(void * data);

static void _dac_write(DAC_channel channel, uint16_t voltage);
static uint8_t harm_getInputs(void);
static void _harm_SetOutputs(uint8_t data);
static void harm_configure(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs);
/* Private functions ---------------------------------------------------------*/

const struct LibraryFunction harm_libs[] =
{
		/*
		 * 1st param:
		 * 	0 disable effect
		 * 	1 enable effect
		 * 	2 toggle effect
		 * 	-1 nothing
		 *
		 * other inputs set effect parameteres in this order: mode,key,harmony,volume
		 * if input -1 then it does nothing
		 * mode, key, harmony 0-? positions of knobs
		 * volume 0-100%
		 *
		 *	returns harmonizer on - 1, off - 0
		 */
	{harm_configure, "int harm_configure(int, int , int ,int ,int);"},
	{	NULL, NULL}};

/**
 * @brief thread for watching harmozier status
 * @notapi
 */
static void harm_thread(void * data)
{

	(void) data;
	uint8_t inputs;
	static bool but, but_old;
	bool temp;
	chRegSetThreadName("harmonist");

	while (TRUE)
	{
		chThdSleepMilliseconds(30);
		inputs = harm_getInputs();

		//if led is different then expected
		//send short pulse to eff output
		temp = harm_getInput_LED(inputs);
		if (temp != _harm_enabled)
		{
			//harm_pushButton(inputs);
			//chThdSleepMilliseconds(50);
			//harm_releaseButton(inputs);
			inputs ^= 1 << HARM_EFF;
			_harm_SetOutputs(inputs);
		}

		//pushing button stated changes send message to consumer thread
		but = harm_getInput_BUT(inputs);
		if (but != but_old)
		{
			but_old = but;
			if (consumer_thd)
			{
				chEvtSignal(consumer_thd, evt_mask);
				chMsgSend(consumer_thd, but);
			}
		}
	}
}

void harm_set_cons_thread(thread_t * thd, eventmask_t mask)
{
	consumer_thd = thd;
	evt_mask = mask;
}

/**
 * @brief set PCA outputs
 * @param[in] bitmask
 * @notapi
 */
void _harm_SetOutputs(uint8_t data)
{
	uint8_t txbuf[2];

	txbuf[0] = PCA_ODR;
	txbuf[1] = data;

	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, HARM_PCA, txbuf, 2, NULL, 0);
	i2cReleaseBus(i2c);
}

/**
 * @brief write harmonist DAC value
 * @notapi
 */
void _dac_write(DAC_channel channel, uint16_t voltage)
{
	uint8_t txbuf[3];

	txbuf[0] = 0b01011000 | ((channel & 0b11) << 1);
	txbuf[1] = (voltage >> 8) & 0xF;
	txbuf[2] = voltage & 0xFF;

	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, DACAN, txbuf, 3, NULL, 0);
	i2cReleaseBus(i2c);
}

/**
 * @brief get PCA expander inputs
 * @return IDR of PCA in harmonizer
 */
uint8_t harm_getInputs(void)
{
	uint8_t txbuf[2];
	uint8_t rxbuf[2];

	txbuf[0] = PCA_IDR;

	i2cAcquireBus(i2c);
	i2cMasterTransmit(i2c, HARM_PCA, txbuf, 1, rxbuf, 2);
	i2cReleaseBus(i2c);

	return (rxbuf[0] & 0x0F);
}

/**
 * @brief setup harmonist default values and PCA setup
 */
void harm_init(I2CDriver * i2cd)
{
	uint8_t txbuf[5];
	i2c = i2cd;

	/*
	 * DAC has own eeprom - memorize last state itself
	 harm_harmony(HARMONIZER.HARMONY.a[0]);
	 harm_key(HARMONIZER.KEY.s.A);
	 harm_mode(HARMONIZER.MODE.s.MAJOR);
	 harm_volume(1000);
	 */

//config PCA Harmonist direction
	txbuf[0] = PCA_DDR;
	txbuf[1] = 0;
//inputs
	txbuf[1] = _BV(HARM_BUT) | _BV(HARM_LED);
//outputs
	i2cAcquireBus(i2c);
	i2cMasterTransmitTimeout(i2c, HARM_PCA, txbuf, 2, NULL, 0,
	TIME_INFINITE);
//set LDAC, EFF
	txbuf[0] = PCA_ODR;
	txbuf[1] = _BV(HARM_LDAC) | _BV(HARM_EFF);
	i2cMasterTransmitTimeout(i2c, HARM_PCA, txbuf, 2, NULL, 0,
	TIME_INFINITE);
	i2cReleaseBus(i2c);

	chThdCreateStatic(&wa_harmonizer, sizeof(wa_harmonizer), NORMALPRIO,
			(tfunc_t) harm_thread, NULL);
}

void harm_configure(struct ParseState *Parser, struct Value *ReturnValue,
		struct Value **Param, int NumArgs)
{
	(void) Parser;
	(void) ReturnValue;
	(void) NumArgs;
	int mode, key, harmony, volume;
	int enable;
	int a = 0;

	enable = Param[0]->Val->Integer;
	mode = Param[1]->Val->Integer;
	key = Param[2]->Val->Integer;
	harmony = Param[3]->Val->Integer;
	volume = Param[4]->Val->Integer;



	uint8_t inputs = harm_getInputs();
	_harm_SetOutputs(inputs & ~_BV(HARM_LDAC));

	if (mode != -1 && mode < HARM_MODE_COUNT)
	{
		harm_mode(mode);
		a++;
		gui_api.harm_mode = mode;
	}
	if (key != -1 && key < HARM_KEY_COUNT)
	{
		harm_key(key);
		a++;
		gui_api.harm_key = key;
	}
	if (harmony != -1 && harmony < HARM_SHIFT_COUNT)
	{
		harm_harmony(harmony);
		gui_api.harm_harmony = harmony;
		a++;
	}
	if (volume > -1 && volume < 101)
	{
		//input value 0-100%
		harm_volume(10 * volume);
		gui_api.harm_volume = volume;
		a++;
	}

	if (a)
	{
		chThdSleepMilliseconds(5);
		harm_setLDAC(inputs);
		_harm_SetOutputs(inputs);
		chThdSleepMilliseconds(5);
	}

	if (enable == 0)
		harm_disable();
	else if (enable == 1)
		harm_enable();
	else if (enable == 2)
		harm_toggle();

	ReturnValue->Val->Integer = _harm_enabled;
}

/**
 * @}
 */

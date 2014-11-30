/**
 * @file gui_api.cpp
 * @author kubanec
 * @date 29. 11. 2014
 *
 */

/* Includes ------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "gui_api.h"
#include "PirisPort.h"

#include "pmaster.h"
#include "pspecialspinbox.h"
#include "pcheckbox.h"
#include "plabel.h"

extern piris::PMaster * mirekGuiInit(piris::PPortingAbstract * port,
		int & size);

static PirisPort pp;
static piris::PMaster* mast;

gui_api_t gui_api;

extern piris::PSpecialSpinBox volume;
extern piris::PSpecialSpinBox gain;
extern piris::PLabel mute;
extern piris::PLabel loop;
extern piris::PLabel high;
extern piris::PSpecialSpinBox harm_volume;
extern piris::PSpecialSpinBox harm_harmony;
extern piris::PSpecialSpinBox harm_key;
extern piris::PSpecialSpinBox harm_mode;
extern piris::PLabel preset;
extern piris::PLabel usb;

void gui_init(void)
{
	pp.start();
	palSetPadMode(GPIOD, 12, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPad(GPIOD, 12);
	int size;
	mast = mirekGuiInit(&pp, size);

	mast->printScreen();
}

void gui_loop(void)
{
	harm_harmony.setValue(gui_api.harm_harmony);
	harm_volume = gui_api.harm_volume;
	harm_key = gui_api.harm_key;
	harm_mode = gui_api.harm_mode;

	volume = gui_api.volume;
	gain = gui_api.gain;

	mute.dirty = true;
	loop.dirty = true;
	high.dirty = true;
	mute.setVisible(gui_api.muteEnabled);
	loop.setVisible(gui_api.loopEnabled);
	high.setVisible(gui_api.highSensitivity);

	if (gui_api.text_dirty)
	{
		preset.dirty = true;
		preset.setText(gui_api.text);
		gui_api.text_dirty = 0;
	}

	usb.dirty = true;
	usb.setVisible(gui_api.usb & 1);

	mast->main();

}

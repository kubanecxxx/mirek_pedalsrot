/**
 * @file PirisPort.cpp
 * @author kubanec
 * @date 28. 7. 2014
 *
 */

#include "ch.h"
#include "hal.h"
#include "PirisPort.h"
#include "pfont.h"
#include "pkeyevent.h"
#include "ptypes.h"
#include "ssd1289_lld.h"
#include "print.h"

extern "C" void __cxa_pure_virtual()
{
	chDbgAssert(0, "pure virtual method called");
	while (1)
		;
}

void * operator new(size_t size)
{
	chDbgAssert(0, "we don't want dynamic allocation");
	return NULL;
}

void PirisPort::start()
{
	tft_InitLCD();
	tft_ClearScreen(LCD_BLACK);
}

bool PirisPort::readKeyEvent(piris::PKeyEvent * evt)
{
	return false;
}
bool PirisPort::readTouchEvent(piris::PTouchEvent *)
{
	return false;
}

#define swap(x) (x == 1) ? 0 : ((((x << 11) & 0xf100) | ((x >> 11) &0x1f) | (x & 0x7E0)))
//#define swap(x) x

void PirisPort::putPixel(piris::pixel_t x, piris::pixel_t y,
		piris::PColor color)
{
	tft_DrawPixel(x, y, color.rawData());
}
void PirisPort::putText(const char * text, piris::pixel_t x, piris::pixel_t y,
		const piris::PFont & font, piris::PColor color)
{
//	St7735::PutString(text, x, y - font.height(), swap(color.rawData()),
//			font.height());
	disp_PutString(text, x, y - font.height(), color.rawData(), font.height());
	//tft_DrawRectangle(0,0,100,50,LCD_YELLOW);

}
void PirisPort::putRectangle(piris::pixel_t x1, piris::pixel_t x2,
		piris::pixel_t y1, piris::pixel_t y2, piris::PColor color, bool filled)
{
	//St7735::DrawRectangle(x1, y1, x2, y2, swap(color.rawData()));
	tft_DrawRectangle(x1, y1, x2, y2, color.rawData());
}
void PirisPort::fill(piris::PColor color)
{
	tft_ClearScreen(color.rawData());
}
void PirisPort::putLine(piris::pixel_t x1, piris::pixel_t x2, piris::pixel_t y1,
		piris::pixel_t y2, piris::PColor color)
{
	//St7735::DrawLine(x1, x2, y1, y2, swap(color.rawData()));
}

piris::pixel_t PirisPort::width() const
{
	return LCD_X_SIZE;
}
piris::pixel_t PirisPort::height() const
{
	return LCD_Y_SIZE;
}

/**
 * @file main_screen.cpp
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

//#include "porting.h"
#include "pkeyevent.h"
#include "pwidget.h"
#include "pmaster.h"
#include "pscreen.h"
#include "qdebugprint.h"
#include "pbutton.h"
#include "pfont.h"
#include "ptouchevent.h"
#include "plabel.h"
#include "pcheckbox.h"
#include "pspecialspinbox.h"

#define MARGIN  5
//fonts
static const DECL_FONT(font8_p,NULL,8,8);
static const DECL_FONT(font16_p,NULL,16,16);
static piris::PFont font8(font8_p);
static piris::PFont font16(font16_p);

//main
static piris::PKeyEvent e;
static piris::PTouchEvent t;
static piris::PMaster mast(&e,&t);


//screen
static const DECL_SCREEN_PROPERTIES(main_screen,piris::BLACK,piris::WHITE,piris::BLUE,&font16,1);
static piris::PScreen main_screen(main_screen_p,&mast);

static const DECL_SPECIALSPINBOX_PROPERTIES(volume, 1,4,1, NULL, NULL,0, NULL,0,"Volume: %d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(volume,MARGIN,20,"",piris::RED,piris::INVALID,NULL,font16_p);
piris::PSpecialSpinBox volume(volume_sp,volume_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(gain, 1,4,1, NULL, NULL,0, NULL,0,"Gain:   %d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(gain,MARGIN,40,"",piris::GREEN,piris::INVALID,NULL,font16_p);
piris::PSpecialSpinBox gain(gain_sp,gain_p,&main_screen);

//name,x,y,w,h,text,textColor,backgroundColor,font, flags
static DECL_LABEL_PROPERTIES(mute,250,10,"Mute", piris::INVALID,piris::INVALID,NULL,font16_p);
piris::PLabel mute (mute_p, NULL);
static DECL_LABEL_PROPERTIES(loop,250,30,"Loop", piris::INVALID,piris::INVALID,NULL,font16_p);
piris::PLabel loop (loop_p, NULL);
static DECL_LABEL_PROPERTIES(high,250,50,"High", piris::INVALID,piris::INVALID,NULL,font16_p);
piris::PLabel high (high_p, NULL);

//name,x,y,text,textColor,backgroundColor,font,fontprops
#define H_OFFSET 80
static const DECL_LABEL_PROPERTIES(h_label, MARGIN, H_OFFSET, "Harmonizer properties",piris::INVALID,piris::INVALID,&font8,font8_p);
static piris::PLabel h_label(h_label_p);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_volume, 0,100,1, NULL, NULL,0, NULL,0,"Volume:%3u",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_volume,MARGIN,H_OFFSET + 12,"",piris::INVALID,piris::INVALID,&font8,font8_p);
 piris::PSpecialSpinBox harm_volume(harm_volume_sp,harm_volume_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_harmony, 0,15,1, NULL, NULL,0, NULL,0,"Harmony:%2d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_harmony,MARGIN  ,H_OFFSET +24 ,"",piris::INVALID,piris::INVALID,&font8,font8_p);
piris::PSpecialSpinBox harm_harmony(harm_harmony_sp,harm_harmony_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_mode, 0,15,1, NULL, NULL,0, NULL,0,"mode: %2d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_mode,MARGIN +100,H_OFFSET + 12,"",piris::INVALID,piris::INVALID,&font8,font8_p);
 piris::PSpecialSpinBox harm_mode(harm_mode_sp,harm_mode_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_key, 0,15,1, NULL, NULL,0, NULL,0,"key:  %2d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_key,MARGIN + 100,H_OFFSET + 24,"",piris::INVALID,piris::INVALID,&font8,font8_p);
 piris::PSpecialSpinBox harm_key(harm_key_sp,harm_key_p,&main_screen);

//name,x,y,text,textColor,backgroundColor,font,fontprops
static DECL_LABEL_PROPERTIES(preset,MARGIN+ 25,150,"testlkasdjflksdjsasd",0xFFE0, piris::INVALID,&font16, font16_p);
piris::PLabel preset(preset_p);

static DECL_LABEL_PROPERTIES(usb,250,200,"USB",piris::WHITE, piris::INVALID,&font16, font16_p);
piris::PLabel usb(usb_p);


piris::PMaster * mirekGuiInit(piris::PPortingAbstract * port, int & size)
{
    mast.setHW(port);

    main_screen.addChild(&mute);
    main_screen.addChild(&loop);
    main_screen.addChild(&high);
    main_screen.addChild(&h_label);
    main_screen.addChild(&preset);
    main_screen.addChild(&usb);

    main_screen.makeActive();

    preset.setText("trouba");


    size = main_screen.dataSize();
    return &mast;
}

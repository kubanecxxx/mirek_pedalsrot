/**
 * @file gui_api.h
 * @author kubanec
 * @date 29. 11. 2014
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GUI_GUI_API_H_
#define GUI_GUI_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint8_t volume;
	uint8_t gain;
	uint8_t loopEnabled;
	uint8_t muteEnabled;
	uint8_t highSensitivity;

	uint8_t harm_mode;
	uint8_t harm_key;
	uint8_t harm_volume;
	uint8_t harm_harmony;

	const char * text;
	uint8_t text_dirty;
	uint8_t usb;
} gui_api_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void gui_init(void);
void gui_loop(void);

extern gui_api_t gui_api;

#ifdef __cplusplus
}
#endif

#endif /* GUI_GUI_API_H_ */

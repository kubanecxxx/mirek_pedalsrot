/**
 * @file picoc_threads.h
 * @author kubanec
 * @date 21. 11. 2014
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MIREK_PEDALSROT_PICOC_USER_PICOC_THREADS_H_
#define MIREK_PEDALSROT_PICOC_USER_PICOC_THREADS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	RELASED, PUSHED
} switch_state;

typedef struct
{
	uint8_t switchNumber;
	switch_state state;
	uint8_t switchNumberOld;
	switch_state stateOld;
	uint32_t ms;
} footswitch_picoc_data_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void picoc_threads_init(void);
void picoc_threads_loop(void);
void ram_enable(bool en);
void picoc_run_picoc_auto_thread(const footswitch_picoc_data_t * foot);
void picoc_threads_terminate_auto_thread(void);

#ifdef __cplusplus
}
#endif

#endif /* MIREK_PEDALSROT_PICOC_USER_PICOC_THREADS_H_ */

/*
 * Led.h
 *
 *  Created on:  20, 2024
 *      Author: Ahmed Adel
 */

#include "STD_TYPES.h"
#include "Led_cfg.h"

#ifndef LED_H_
#define LED_H_
//=================================defines================================//
#define  LED_STATE_ON  1
#define  LED_STATE_OFF 0

#define  LED_Connection_foward  1
#define  LED_Connection_Reverse 0
//===================================Types=================================//

typedef struct {
	void* LED_Port;
	u32 LED_Pin;
	u32 LED_Connection;
	u32 LED_MODE;
	u32 LED_Speed;


}Led_cfg_t;

typedef enum{
	LED_OK,
	LED_INVALID_status,
	LED_INVALID_led,

}LED_errorstate_t;

//==================================API's=====================================//


LED_errorstate_t Led_SetStatus (u32 Led,u8 States);

LED_errorstate_t Led_init (void);

#endif /* LED_H_ */

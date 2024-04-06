/*
 * LED.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohammed Hani
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "STD_TYPES.h"
#include "Switch_cfg.h"
#include "GPIO.h"

typedef struct
{
    u32 Port;
    u32 Pin;
    u8 State;
}Switch_cfg_t;

typedef enum
{
    Switch_OK,
	Switch_enuInvalidPortNum,
	Switch_enuInvalidPinNum,
	Switch_enuInvalidMode,
	Switch_enuNullPtr,
    Switch_NOK
}Switch_ErrorStatus_t;



#define 	SWITCH_UNPRESSED	    0
#define 	SWITCH_PRESSED  		1

void Switch_Init(void);

void Switch_GetSwitchState(u32 SwitchName, u8 *Add_SwitchState);


#endif /* SWITCH_H_ */

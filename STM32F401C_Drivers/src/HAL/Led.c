/*
 * Led.c
 *
 *  Created on:  20, 2024
 *      Author: Ahmed Adel
 */

#include "Led.h"
#include "GPIO.h"

extern  const Led_cfg_t LEDS[_LED_Num];


//========================================LED_init=========================================//
LED_errorstate_t Led_init (void){

	LED_errorstate_t local_errorstate= LED_OK;
	GPIO_Pinconfig_t local_LED;
	u32 counter;
	for (counter=0;counter<_LED_Num;counter++){
		local_LED.GPIO_portnumber=LEDS[counter].LED_Port;
		local_LED.GPIO_pinnumber=LEDS[counter].LED_Pin;
		local_LED.GPIO_MODE=LEDS[counter].LED_MODE;
		local_LED.GPIO_SPEED=LEDS[counter].LED_Speed;
		local_errorstate=Gpio_enuInit(&local_LED);
	}

	return local_errorstate;
}

//==========================================Set_LED_state============================================//

LED_errorstate_t Led_SetStatus (u32 Led,u8 States){

	LED_errorstate_t local_errorstate= LED_OK;
	if (Led>_LED_Num){
		local_errorstate = LED_INVALID_led;
	}
	else if (!(States == LED_STATE_ON)||( States== LED_STATE_OFF)){
        local_errorstate =LED_INVALID_status;
	}
	else{
		local_errorstate=GPIO_SetPin_value(LEDS[Led].LED_Port,LEDS[Led].LED_Pin,LEDS[Led].LED_Connection^States);
	}
	return local_errorstate;
}

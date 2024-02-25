/*
 * Switch.c
 *
 *  Created on:  20, 2024
 *      Author: Ahmed Adel
 */

#include "Switch.h"
#include "GPIO.h"

extern const Switch_cfg_t Switchs [_Switch_num];

Switch_errorstate_t Switch_Get_state (u32 copy_Switch , u8* copy_state){

	Switch_errorstate_t local_reterror =Switch_ok ;

	GPIO_Pinconfig_t loc_Switch;
	u32 idx=0;



	for( idx=0; idx<_Switch_num ;idx++){
		loc_Switch.GPIO_portnumber=  Switchs[idx].Switch_port;
		loc_Switch.GPIO_pinnumber=  Switchs[idx].Switch_pin;
		loc_Switch.GPIO_MODE=  Switchs[idx].Switch_Mode;

		if (Switchs[idx].Switch_Mode== Switch_input_PU){

			loc_Switch.GPIO_MODE=GPIO_MODE_INPUT_PU;
		}

		else{
			loc_Switch.GPIO_MODE=GPIO_MODE_INPUT_PD;

		}
		local_reterror =Gpio_enuInit(&loc_Switch);
	}
	return local_reterror;
}

//=======================================================================================================================//

Switch_errorstate_t SWITCH_Get_Read(u32 Switch_num,u32* Read){
	Switch_errorstate_t Local_Error=Switch_ok;
	u32 helper;
	if (Switch_num>_Switch_num){
		Local_Error=Switch_nok;
	}
	else if(Read==NULL){
		Local_Error=Switch_nok;
	}
	else{
		GPIO_Get_Pin_Value(Switchs[Switch_num].Switch_port,Switchs[Switch_num].Switch_pin,&helper);
	}
	switch(Switchs[Switch_num].Switch_Mode){
	case GPIO_MODE_INPUT_PU: *Read=!helper;
	break;
	case GPIO_MODE_INPUT_PD: *Read=helper;
	break;
	case GPIO_MODE_INPUT_FLOATING: * Read=helper;
	break ;
	default: Local_Error=Switch_nok;
	break;
	}
	return Local_Error;
}


//================================================================================================================//

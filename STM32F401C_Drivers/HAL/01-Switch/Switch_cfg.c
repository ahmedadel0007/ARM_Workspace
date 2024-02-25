/*
 * Switch_cfg.c
 *
 *  Created on: 20, 2024
 *      Author: Ahmed Adel
 */


#include "GPIO.h"
#include "Switch.h"



const Switch_cfg_t Switchs[_Switch_num]=
{
		[Switch_007]={.Switch_port=GPIO_A,
				      .Switch_pin=GPIO_PIN0,
					  .Switch_Mode= Switch_input_PU,
		},
		[Switch_Alarm]={.Switch_port=GPIO_A,
			            .Switch_pin=GPIO_PIN1,
				        .Switch_Mode= Switch_input_PD,

		}
};


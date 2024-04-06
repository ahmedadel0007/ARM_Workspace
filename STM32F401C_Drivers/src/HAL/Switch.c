/*
 * LED.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Ahmed
 */

#include "GPIO.h"

#include "Switch.h"

u8 SwitchesStates[_Switch_Num];

extern const Switch_cfg_t SWITCHEs[_Switch_Num];

void Switch_Init(void)
{
	u8 Local_Iterator;
	GPIO_Pinconfig_t Switch_cfg;
	Switch_cfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	Switch_cfg.GPIO_SPEED = GPIO_SPEED_HIGH;
  


	for(Local_Iterator = 0; Local_Iterator < _Switch_Num; Local_Iterator++)
	{
		Switch_cfg.GPIO_portnumber = SWITCHEs[Local_Iterator].Port;
		Switch_cfg.GPIO_pinnumber =  SWITCHEs[Local_Iterator].Pin;
		Switch_cfg.GPIO_MODE = SWITCHEs[Local_Iterator].State;
		Gpio_enuInit(&Switch_cfg);
	}
}

void Switch_GetSwitchState(u32 SwitchName, u8 *Add_SwitchState)
{
    *Add_SwitchState = SwitchesStates[SwitchName];

     u32 Loc_Temp = 0 ;
    if(SWITCHEs[SwitchName].State == GPIO_MODE_INPUT_PU)
    {
      Loc_Temp = 1 ;
    }
    else
    {
      Loc_Temp = 0 ;
    }
    *Add_SwitchState = *Add_SwitchState ^ Loc_Temp;
}

void SWITCH_Runabble(void)
{
	static u8 counter[_Switch_Num];
	static u8 current;
	static u8 pervious[_Switch_Num];
	u8 localindex;
	for (localindex = 0; localindex < _Switch_Num; localindex++)
	{
		GPIO_GetPin_value(SWITCHEs[localindex].Port, SWITCHEs[localindex].Pin,&current);
		if (current == pervious[localindex])
		{
			counter[localindex]++;
		}
		else
		{
			counter[localindex] = 0;
		}
		if (counter[localindex] % 5 == 0)
		{
			SwitchesStates[localindex] = current;
		}
		pervious[localindex] = current;
	}
}
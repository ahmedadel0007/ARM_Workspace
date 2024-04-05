/*
 * Switch.c
 * Created on: Feb 26, 2024
 * Author: Ahmed Adel 
 */
#include "Switch.h"

extern SWITCHCFG_str Switches[_SWITCH_NUM];

u8 SwitchesStates[_SWITCH_NUM];

Switch_ErrorState_t SWITCH_init(void)
{
	Switch_ErrorState_t RETURN_ERRORSTATUS = Switch_OK;
	u8 localCounter, Errorcheck = 0;
	GPIO_Pinconfig_t Switch;
	Switch.GPIO_SPEED = GPIO_SPEED_HIGH;
	for (localCounter = 0; localCounter < _SWITCH_NUM; localCounter++)
	{
		Switch.GPIO_portnumber = Switches[localCounter].SwitchPORT;
		Switch.GPIO_pinnumber = Switches[localCounter].SwitchPINnumber;
		if (Switches[localCounter].SwitchConnection == SWITCH_PULLUP){
		Switch.GPIO_MODE = GPIO_MODE_INPUT_PU;
		}
		else {
         Switch.GPIO_MODE = GPIO_MODE_INPUT_PD;
		}
		RETURN_ERRORSTATUS = Gpio_enuInit(&Switch);
		if (RETURN_ERRORSTATUS != Switch_OK)
		{
			Errorcheck++;
		}
	}
	if (Errorcheck == 0)
	{
		RETURN_ERRORSTATUS = Switch_OK;
	}
	else
	{
		RETURN_ERRORSTATUS = Switch_NOK;
	}
	return RETURN_ERRORSTATUS;
}

Switch_ErrorState_t SWITCH_GETSTATUS(SWITCHES_enu Switchname, u16 *SwitchStatus)
{
	Switch_ErrorState_t RETURN_ERRORSTATUS = Switch_NOK;
	if (Switchname > _SWITCH_NUM)
	{
		RETURN_ERRORSTATUS = Switch_NOK;
	}
	else if (SwitchStatus == NULL)
	{
		RETURN_ERRORSTATUS = Switch_Nullptr;
	}
	else
	{
		RETURN_ERRORSTATUS =Switch_OK ;
		*SwitchStatus = SwitchesStates[Switchname];
		if (Switches[Switchname].SwitchConnection == SWITCH_PULLUP)
		{
			*SwitchStatus = *SwitchStatus ^ 1;
		}
	}
		return RETURN_ERRORSTATUS;
}

void SWITCH_Runabble(void)
{
	static u8 counter[_SWITCH_NUM];
	static u32 current;
	static u8 pervious[_SWITCH_NUM];
	u8 localindex;
	for (localindex = 0; localindex < _SWITCH_NUM; localindex++)
	{
		GPIO_GetPin_value(Switches[localindex].SwitchPORT, Switches[localindex].SwitchPINnumber,&current);
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
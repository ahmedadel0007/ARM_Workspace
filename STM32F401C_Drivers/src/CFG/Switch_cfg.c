#include "Switch.h"


SWITCHCFG_str Switches [_SWITCH_NUM ]=
{

	[Switch_mode]=
		{
				.SwitchPORT = SWITCH_PORTB,
				.SwitchPINnumber = SWITCH_PIN12,
				.SwitchConnection = SWITCH_PULLUP,
		},
		[Switch_up]=
		{
				.SwitchPORT = SWITCH_PORTA,
				.SwitchPINnumber = SWITCH_PIN1,
				.SwitchConnection = SWITCH_PULLUP,
		},
		[Switch_down]=
		{
				.SwitchPORT = SWITCH_PORTA,
				.SwitchPINnumber = SWITCH_PIN2,
				.SwitchConnection = SWITCH_PULLUP,
		},    
		[Switch_right]=
		{
				.SwitchPORT = SWITCH_PORTA,
				.SwitchPINnumber = SWITCH_PIN4,
				.SwitchConnection = SWITCH_PULLUP,
		},
		[Switch_left]=
		{
				.SwitchPORT = SWITCH_PORTA,
				.SwitchPINnumber = SWITCH_PIN3,
				.SwitchConnection = SWITCH_PULLUP,
		}
								
};
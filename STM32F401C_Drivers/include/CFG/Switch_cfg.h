
#ifndef SWITCHCFG_H_
#define SWITCHCFG_H_

typedef enum
{
	Switch_mode,
	Switch_up,
	Switch_down,
	Switch_right,
	Switch_left,


	_SWITCH_NUM  /*THE USER SHOULDNOT CHANGE IT */
}SWITCHES_enu;

typedef struct
{
	void* SwitchPORT;
	u32 SwitchPINnumber;
	u32 SwitchConnection;
}SWITCHCFG_str;


#endif  /*SWITCHCFG_H_*/

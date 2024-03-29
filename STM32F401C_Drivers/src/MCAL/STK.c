/*
 ============================================================================
 Name        : STK.c
 Author      : Ahmed Adel
 Description : STK Source File
 Date        : 11/3/2024
 ============================================================================
 */
//============================Includes=====================================================//

#include "STK.h"

//=============================Types=====================================================//
typedef struct {
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;


}STK_Reg_t;

//=========================Defines===================================================//
#define STK_BASS_ADDRESS  0xE000E010
#define STK_START_STOP    0x00000001
#define STK_SRC           0x00000004
#define STK_Clear_Mode    0xFFFFFFF9
#define LOW_RELOAD_VAL    0x00000001
#define HIGH_RELOAD_VAL   0x00FFFFFF
#define CLK_Frequency_IN_MHZ 16000000




//===================Pointers==================================================//
volatile STK_Reg_t *const STK = (volatile STK_Reg_t*) STK_BASS_ADDRESS;

static STK_CBF_t APP_CBF = NULL ;


//=============================Implementation===========================================//
STK_ERRORSTATE_t  STK_Strat (void){

	STK_ERRORSTATE_t Local_reterror = STK_OK;

	u32 local_ret= STK->STK_CTRL;

	/*set Start*/
	local_ret |= STK_START_STOP ;

	STK->STK_CTRL =local_ret;

	return Local_reterror;
}

//===============================================================================//
STK_ERRORSTATE_t  STK_Stop (void){

	STK_ERRORSTATE_t Local_reterror = STK_OK;

	u32 local_ret= STK->STK_CTRL;

	/*set Start*/
	local_ret &=  ~(STK_START_STOP) ;

	STK->STK_CTRL =local_ret;

	return Local_reterror;
}

//===========================================================================================================//
STK_ERRORSTATE_t  STK_SetTimeMS (u32 timeMS){

	STK_ERRORSTATE_t 	local_reterror= STK_OK ;

	/*calculate the Mp frequency */

	u32 Local_Mp_freq = ((STK ->STK_CTRL)&(STK_SRC)) ? CLK_Frequency_IN_MHZ : CLK_Frequency_IN_MHZ/ 8;

	/*calculate the Reload value */

	u32 Reload_value = (timeMS *Local_Mp_freq /1000) - 1 ;

	/*check if it exceds the bounderies */
	if ((timeMS <LOW_RELOAD_VAL) ||(timeMS > HIGH_RELOAD_VAL)){
		local_reterror = STK_NOK ;
	}
	else {
		/*set The preload value*/
		STK->STK_LOAD =Reload_value;

		/*clear the current*/
		STK->STK_VAL = 0;
	}
	return local_reterror;
}
//===============================================================================================//

STK_ERRORSTATE_t  STK_SetConfig (u32 Mode){

	STK_ERRORSTATE_t local_error= STK_OK;

	u32 local_ret = STK->STK_CTRL;

	if (Mode != STK_ProcessorClock_NO_INT &&
			Mode != STK_ProcessorClock_EN_INT &&
			Mode != STK_AHB_8_EN_INT &&
			Mode != STK_AHB_8_NO_INT)
	{
		local_error= STK_WrongMode;
	}
	else {
		local_ret &= STK_Clear_Mode ;
		local_ret |= Mode;

		STK->STK_CTRL =local_ret;

	}
   return local_error;
}

//=============================================================================================//


STK_ERRORSTATE_t  STK_SetCallBack (STK_CBF_t CBF){

	STK_ERRORSTATE_t local_error= STK_OK;

	if (CBF != NULL)
	{
		APP_CBF =CBF;
	}
	else
	{
	 local_error= STK_NULLPTR;
	}

	return local_error;
}
//=========================================================================================//
void SysTick_Handler()
{
	if (APP_CBF)
	{
		APP_CBF();
	}
}


/*
 ============================================================================
 Name        : NVIC.c
 Author      : Ahmed Adel
 Description : Header File for the NVIC Driver
 Date        : 5/3/2024
 ============================================================================
 */

#include "NVIC.h"

NVIC_ERRORSTATE_t  NVIC_EnableInterrupt (u8 Copy_InterrputID){

	NVIC_ERRORSTATE_t local_errorstate = NVIC_OK ;

	u8 local_Register;
	u8 local_Bit;

	if (Copy_InterrputID > NVIC_TotalInterrputs){
		local_errorstate= NVIC_INVAILD_INT_NUMBER;

	}
	else {
		local_Register= Copy_InterrputID / 32 ;

		local_Bit=Copy_InterrputID % 32 ;

		NVIC_ISER_BASE[local_Register] |= (1<<local_Bit) ;

		local_errorstate = NVIC_OK ;

	}
	return local_errorstate;

}
//===============================================================================================================//

NVIC_ERRORSTATE_t NVIC_DisableInterrput (u8 Copy_InterrputID){
	NVIC_ERRORSTATE_t local_errorstate = NVIC_OK ;

	u8 local_Register;
	u8 local_Bit;

	if (Copy_InterrputID > NVIC_TotalInterrputs){
		local_errorstate= NVIC_INVAILD_INT_NUMBER;

	}
	else {
		local_Register= Copy_InterrputID / 32 ;

		local_Bit=Copy_InterrputID % 32 ;

		NVIC_ICER_BASE[local_Register] |= (1<<local_Bit) ;

		local_errorstate = NVIC_OK ;

	}
	return local_errorstate;

}
//==============================================================================================//

NVIC_ERRORSTATE_t  NVIC_SetPending (u8 Copy_InterrputID){

	NVIC_ERRORSTATE_t local_errorstate =NVIC_OK;

	u8 local_Register ;
	u8 local_Bit ;

	if (Copy_InterrputID > NVIC_TotalInterrputs){
		local_errorstate = NVIC_INVAILD_INT_NUMBER;

	}

	else{
		local_Register = Copy_InterrputID / 32;

		local_Bit = Copy_InterrputID % 32;

		NVIC_ISPR_BASE[local_Register] |= (1<<local_Bit);
	}

	return local_errorstate ;

}

//===========================================================================================================//

NVIC_ERRORSTATE_t  NVIC_ClearPending (u8 Copy_InterrputID){


	NVIC_ERRORSTATE_t local_errorstate =NVIC_OK;

	u8 local_Register ;
	u8 local_Bit ;

	if (Copy_InterrputID > NVIC_TotalInterrputs){
		local_errorstate = NVIC_INVAILD_INT_NUMBER;

	}

	else{
		local_Register = Copy_InterrputID / 32;

		local_Bit = Copy_InterrputID % 32;

		NVIC_ICPR_BASE[local_Register] |= (1<<local_Bit);
	}

	return local_errorstate ;

}
//==========================================================================================================//


NVIC_ERRORSTATE_t  NVIC_GetActiveState (u8 Copy_InterrputID, u8* Active_value){

	NVIC_ERRORSTATE_t local_errorstate =NVIC_OK;

	u8 local_Register ;
	u8 local_Bit ;

	if (Copy_InterrputID > NVIC_TotalInterrputs){
		local_errorstate = NVIC_INVAILD_INT_NUMBER;

	}
	else {
		local_Register = Copy_InterrputID / 32 ;

		local_Bit =Copy_InterrputID % 32 ;

		* Active_value=((*(NVIC_IAB_BASE+local_Register))>>local_Bit)  &  1  ;
	}

	return local_errorstate;
}

//============================================================================================================//


NVIC_ERRORSTATE_t NVIC_SetPriority (u8 Copy_InterrputID , u8 Copy_priority){

	NVIC_ERRORSTATE_t local_errorstate =NVIC_OK;

	u8 local_Register ;
	u8 local_Bit ;

	if (Copy_InterrputID > NVIC_TotalInterrputs)
	{
		local_errorstate = NVIC_INVAILD_INT_NUMBER;

	}
	else if (Copy_priority > NVIC_SPI4_INTERRUPT)
	{
		local_errorstate =NVIC_INVAILD_Priority;
	}

	else
	{
		local_Register = Copy_InterrputID / 4;

		local_Bit = ((Copy_InterrputID % 4)*8)+4;

		NVIC_IPR_BASE[local_Register] |= Copy_priority << (local_Bit<<4);

		local_errorstate =NVIC_OK;
	}

	return local_errorstate ;

}
//=============================================================================================================================================//

/* choose a Sub Group from The following Choice :
1- NVIC_PRIORITYGROUP_16_NONE    (0x0UL << 8)  // None bits group, 16 bits sub priority
2- NVIC_PRIORITYGROUP_8_2        (0x4UL << 8)  // 8 bits group, 2 bits sub priority
3- NVIC_PRIORITYGROUP_4_4        (0x5UL << 8)  // 4 bits group, 4 bits sub priority
4- NVIC_PRIORITYGROUP_2_8        (0x6UL << 8)  // 2 bits group, 8 bits sub priority
5- NVIC_PRIORITYGROUP_NONE_16    (0x7UL << 8)  // None bits group, 16 bits sub priority*/
//============================================================================================================================================//
NVIC_ERRORSTATE_t NVIC_SetSubPriority (u8 Group_Number ){

	NVIC_ERRORSTATE_t local_errorstate = NVIC_INVAILD_GROUP_NUMBER ;

	u32 Loc_Aircr = SCB_AIRCR ;
	Loc_Aircr &= AIRCR_Clear ;
	Loc_Aircr|=Group_Number;
	SCB_AIRCR = Loc_Aircr;

	return local_errorstate ;
}

//=======================================================================================================================//




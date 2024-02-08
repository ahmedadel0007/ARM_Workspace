/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Ahmed Adel Abdalla
 *  Date    : 5/2/2024
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */



/* include Libraries  */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* include files of lower layer */
// Nothing Because this driver in MCAL Layer

/* Own Driver Files */
#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"




//==============================================================================================================//
Rcc_tenuErrorStatus Rcc_SetClockOn(u32 Copy_u32ClockSelection){

	Rcc_tenuErrorStatus loc_tenuErrorStatus;
	loc_tenuErrorStatus = Rcc_OK;

	switch (Copy_u32ClockSelection)
	{
		case HSI_CLOCK:

			RCC_CR |= 0x00000001;
			break;

		case HSE_CLOCK:

			RCC_CR |= 0x00010000;
			break;

		case PLL_CLOCK:

			RCC_CR |= 0x01000000;
			break;

		default:
			loc_tenuErrorStatus = Rcc_InputError;
			break;
	}
	return loc_tenuErrorStatus;
}

//==============================================================================================================//

Rcc_tenuErrorStatus	Rcc_PllConfiguration(u8 Copy_u8PllM, u16 Copy_u16PllN, u8 Copy_u8PllQ, u8 Copy_u8PllP)
{
	Rcc_tenuErrorStatus loc_tenuErrorStatus;
	loc_tenuErrorStatus = Rcc_OK;

	u32 loc_U32clearvariable;

	if (RCC_CR & (PLL_CLOCK & 0xDFFFFFFF) )
	{
	  loc_tenuErrorStatus = Rcc_PllEnable ;
    }

	/* check the range for pll M factor*/
	else if (Copy_u8PllM < 2 || Copy_u8PllM > 63)
	{
		loc_tenuErrorStatus = Rcc_InputRangeError;
	}
	/* check the range for pll N factor*/
	else if (Copy_u16PllN < 192 || Copy_u16PllN > 432)
	{
		loc_tenuErrorStatus = Rcc_InputRangeError;
	}
	/* check the range for pll Q factor*/
	else if (Copy_u8PllQ < 2 || Copy_u8PllQ > 15)
	{
		loc_tenuErrorStatus = Rcc_InputRangeError;
	}
	/* check the range for pll P factor*/
	else if (Copy_u8PllP != 2 || Copy_u8PllP != 4 || Copy_u8PllP != 6 || Copy_u8PllP != 8 )
	{
		loc_tenuErrorStatus = Rcc_InputRangeError;
	}
	else
	{
		/*To clear all values in the register PLL Configuration*/
				loc_U32clearvariable = 0x00400000;
				RCC_PLLCFGR &= loc_U32clearvariable;

				/*Set the values of the configuration*/
				loc_U32clearvariable = Copy_u8PllQ<<24 | Copy_u8PllP<<16 | Copy_u16PllN<<6 | Copy_u8PllM;
				RCC_PLLCFGR |= loc_U32clearvariable;


	}
	return loc_tenuErrorStatus ;

}

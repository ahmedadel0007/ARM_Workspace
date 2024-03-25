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


/* include files of lower layer */
// Nothing Because this driver in MCAL Layer

/* Own Driver Files */
#include "RCC_interface.h"


/*static RCC_Pointer_t * RCC=(RCC_Pointer_t *)(0x40023800);*/


//==============================================================================================================//
Rcc_enuErrorStatus	Rcc_SelectsystemClk (u32 Copy_ClockSelection)
{
	Rcc_enuErrorStatus Return_systemclk =RCC_OK ;
	u32 local_CFGRresgister ;
	u32 local_timeout=0 ;

	/* CHECKING ERROR : RIGHT CLOCK */
	if((Copy_ClockSelection >= RCC_HSI) || (Copy_ClockSelection <= RCC_PLL))
	{
		switch ( Copy_ClockSelection)
		{
		case RCC_HSI:
		{
			/*check on*/
			if ((Copy_ClockSelection & MASK_HSI_ON)== MASK_HSI_ON)
			{
				/*check Ready*/
				if ((Copy_ClockSelection & MASK_HSI_RDY)==MASK_HSI_RDY)
				{
					/*set sysclk as HSI*/
					local_CFGRresgister = RCC_CFGR;
					local_CFGRresgister &= ~MASK_SW;     /*clear*/
					local_CFGRresgister |= (RCC_HSI);  /*set*/
					RCC_CFGR = local_CFGRresgister;
					/*wait until ready*/
					while( ((RCC_CFGR & MASK_GET_SWS) != MASK_SWS_HSI) && (local_timeout<100000))
					{
						local_timeout++;
					}
					if( local_timeout >= 100000 )
					{
						/* TIMEOUT */
						Return_systemclk= RCC_NotOK;
					}
					else {
						Return_systemclk=RCC_NotOK;
					}
				}
				else
				{
					Return_systemclk=RCC_NotOK;
				}
			}
			break ;

		}

		case RCC_HSE :
		{
			/*check on*/



					local_CFGRresgister  = RCC_CFGR;
					local_CFGRresgister  &= ~MASK_SW;
					local_CFGRresgister  |= (RCC_HSE);
					RCC_CFGR = local_CFGRresgister ;

					while(( (RCC_CFGR&MASK_SWS_HSE)!=MASK_SWS_HSE) && ((local_timeout)<100000))
					{
						local_timeout++;
					}
					if( local_timeout >= 100000 )
					{

						/* TIMEOUT */
						Return_systemclk = RCC_NotOK;
					}






			/* CLOCK OFF */


		break ;
		}

		case RCC_PLL:
		{
			/*check on*/
			if ((Copy_ClockSelection & MASK_PLL_ON)== MASK_PLL_ON)
			{
				/*check Ready*/
				if ((Copy_ClockSelection & MASK_PLL_RDY)==MASK_PLL_RDY)
				{
					/*set sysclk as HSI*/
					local_CFGRresgister = RCC_CFGR;
					local_CFGRresgister &= ~MASK_SW;     /*clear*/
					local_CFGRresgister |= (RCC_PLL);  /*set*/
					RCC_CFGR = local_CFGRresgister;
					/*wait until ready*/
					while( ((RCC_CFGR & MASK_GET_SWS) != MASK_SWS_PLL) && (local_timeout<100000))
					{
						local_timeout++;
					}
					if( local_timeout >= 100000 )
					{
						/* TIMEOUT */
						Return_systemclk= RCC_NotOK;
					}
					else
					{
						Return_systemclk=RCC_NotOK;
					}
				}
				else
				{
					Return_systemclk=RCC_NotOK;
				}
			}
			/* CLOCK OFF */
			else{
				Return_systemclk = RCC_NotOK;
			}
			break;
		}
		}
	}
		return Return_systemclk;
		}


		//==============================================================================================================//
		Rcc_enuErrorStatus  RCC_ControlClk(u8 Copy_ClockSystem,RCC_enuClkStatus Copy_enuClkStatus)
		{

			u32 Loc_systemclk = ((RCC_CFGR & MASK_GET_SYSCLK)>>2);
			Rcc_enuErrorStatus  Return_systemclk = RCC_OK;
			u32 local_timeout = 0;

			/* ERROR : CHANGING ON THE SYSTEM CLOCK */
			if(Loc_systemclk == Copy_ClockSystem)
			{
				Return_systemclk = RCC_NotOK ;
			}

			/* ERROR : CHOOSING WRONG CLOCK */
			else if ( !(Copy_ClockSystem == RCC_HSI) && (Copy_ClockSystem == RCC_PLL))
			{
				Return_systemclk = RCC_NotOK;
			}

			else{
				switch(Copy_ClockSystem)
				{

				/* CONTROL HSI CLK ON/OFF */
				case RCC_HSI:
					if(Copy_ClockSystem == OFF)
					{
						RCC_CR &= (~MASK_SET_HSI); /*clear*/
					}
					else
					{
						RCC_CR |= (MASK_SET_HSI);  /*set*/
						while (((RCC_CR & MASK_HSI_RDY)==0)&&(Loc_systemclk<100000))
						{
							local_timeout++;
						}
						if (local_timeout >= 100000)
						{
							Return_systemclk =RCC_NotOK;
						}
					}
					break ;

					/* CONTROL HSI CLK ON/OFF */
				case RCC_HSE:
					if(Copy_ClockSystem == OFF)
					{
						RCC_CR &= (~MASK_SET_HSE); /*clear*/
					}
					else
					{
						RCC_CR |= (MASK_SET_HSE);  /*set*/
						while (((RCC_CR & MASK_HSE_RDY)==0)&&(Loc_systemclk<100000))
						{
							local_timeout++;
						}
						if (local_timeout >= 100000)
						{
							Return_systemclk =RCC_NotOK;
						}
					}
					break ;
					/* CONTROL HSI CLK ON/OFF */
				case RCC_PLL:
					if(Copy_ClockSystem == OFF)
					{
						RCC_CR &= (~MASK_SET_PLL); /*clear*/
					}
					else
					{
						RCC_CR |= (MASK_SET_PLL);  /*set*/
						while (((RCC_CR & MASK_PLL_RDY)==0)&&(Loc_systemclk<100000))
						{
							local_timeout++;
						}
						if (local_timeout >= 100000)
						{
							Return_systemclk =RCC_NotOK;
						}
					}
					break ;
				}
			}
			return Return_systemclk ;
		}
		//==============================================================================================================//

		Rcc_enuErrorStatus  RCC_enuCheckReady(u8 Copy_u8ClockSystem, u8* Add_pu8ReadyStatus){
			Rcc_enuErrorStatus Ret_enuSystemCLOCK = RCC_OK;


			if(!(Copy_u8ClockSystem == RCC_HSI) || (Copy_u8ClockSystem == RCC_PLL) || (Copy_u8ClockSystem == RCC_HSE)){

				switch(Copy_u8ClockSystem){

				/* GET HSI CLK READY/NOT_READY */
				case RCC_HSI:
					if((RCC_CR&MASK_GET_RDY_HSI) == MASK_GET_RDY_HSI){
						*Add_pu8ReadyStatus = RCC_RDY_STATUS;
					}
					else{
						*Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
					}
					break;

					/* GET HSE CLK READY/NOT_READY */
				case RCC_HSE:
					if((RCC_CR&MASK_GET_RDY_HSE) ==MASK_GET_RDY_HSE){
						*Add_pu8ReadyStatus = RCC_RDY_STATUS;
					}
					else{
						*Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
					}
					break;

					/* GET PLL CLK READY/NOT_READY */
				case RCC_PLL:
					if((RCC_CR&MASK_GET_RDY_PLL) == MASK_GET_RDY_PLL){
						*Add_pu8ReadyStatus = RCC_RDY_STATUS;
					}
					else{
						*Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
					}

					break;
				}
			}

			/* ERROR : CLOCK IS NOT TRUE */
			else{
				Ret_enuSystemCLOCK = RCC_NotOK;
			}

			return Ret_enuSystemCLOCK;
		}

		//==============================================================================================================//

		Rcc_enuErrorStatus  RCC_enuConfigPLL(RCC_structCLKPLL Copy_structPLLCongif)
		{
			Rcc_enuErrorStatus Loc_enuerrorstatusPLL = RCC_OK;

			RCC_enuPLLSRC Loc_enuPLLSource = Copy_structPLLCongif.RCC_enuPLLSCR;
			u32 Loc_PLL_M = Copy_structPLLCongif.RCC_enuPLL_M;
			u32 Loc_PLL_N = Copy_structPLLCongif.RCC_enuPLL_N;
			u32 Loc_PLL_P = Copy_structPLLCongif.RCC_enuPLL_P;
			u32 Loc_PLL_Q = Copy_structPLLCongif.RCC_enuPLL_Q;

			u32 Loc_u32PLLCFGR_Register;

			/* CHECKING ERROR : M CONFIGURATION */
			if(Loc_PLL_M == 0 || Loc_PLL_M == 1 || Loc_PLL_M > 63){
				Loc_enuerrorstatusPLL = RCC_NotOK;
			}

			/* CHECKING ERROR : N CONFIGURATION */
			else if(Loc_PLL_N == 0 || Loc_PLL_N == 1 || Loc_PLL_N == 433 || Loc_PLL_N >= 511){
				Loc_enuerrorstatusPLL = RCC_NotOK;
			}

			/* CHECKING ERROR : P CONFIGURATION */
			else if((Loc_PLL_P != 2) && (Loc_PLL_P != 4) && (Loc_PLL_P != 6) && (Loc_PLL_P != 8)){
				Loc_enuerrorstatusPLL = RCC_NotOK;
			}

			/* CHECKING ERROR : Q CONFIGURATION */
			else if(Loc_PLL_Q == 0 || Loc_PLL_Q == 1 || Loc_PLL_Q > 15){
				Loc_enuerrorstatusPLL = RCC_NotOK;
			}

			/* CHECKING ERROR : CLOCK SOURCE */
			else if(Loc_enuPLLSource>HSE){
				Loc_enuerrorstatusPLL = RCC_NotOK;
			}

			/* CHICKING ERROR : PLL ON */
			else if((RCC_CR&MASK_GET_ON_PLL) != OFF){
				Loc_enuerrorstatusPLL = RCC_NotOK;
			}

			else
			{

				/*** CONFIGURE THE PPL ***/
				/* 1: CONFIGURE M */
				Loc_u32PLLCFGR_Register = RCC_PLLCFGR;
				Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_M;
				Loc_u32PLLCFGR_Register |= (Loc_PLL_M<<SHIFT_PLL_M);
				RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

				/* 2: CONFIGURE N */
				Loc_u32PLLCFGR_Register = RCC_PLLCFGR;
				Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_N;
				Loc_u32PLLCFGR_Register |= (Loc_PLL_N<<SHIFT_PLL_N);
				RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

				/* 3: CONFIGURE P */
				Loc_u32PLLCFGR_Register = RCC_PLLCFGR;
				Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_P;
				Loc_u32PLLCFGR_Register |= (Loc_PLL_P<<SHIFT_PLL_P);
				RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

				/* 4: CONFIGURE Q */
				Loc_u32PLLCFGR_Register = RCC_PLLCFGR;
				Loc_u32PLLCFGR_Register &= ~ MASK_SET_PPL_Q;
				Loc_u32PLLCFGR_Register |= (Loc_PLL_Q<<SHIFT_PLL_Q);
				RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

				/* 5: CONFIGURE CLOCK SOURCE */
				Loc_u32PLLCFGR_Register = RCC_PLLCFGR;
				Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_SRC;
				Loc_u32PLLCFGR_Register |= (Loc_enuPLLSource<<SHIFT_PLL_SRC);
				RCC_PLLCFGR = Loc_u32PLLCFGR_Register;
			}

			return Loc_enuerrorstatusPLL;

		}

		//==============================================================================================================//


		Rcc_enuErrorStatus  RCC_enuControlPrescalerAHB(u32 Copy_AHBPrescaler){

			Rcc_enuErrorStatus Return_errorstatus = RCC_OK;
			u32 local_CFGRregister;

			switch (Copy_AHBPrescaler){
			case AHB_NO_CLOCK_FACTOR:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_NO_CLOCK_FACTOR<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_2:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_2<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_4:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_4<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_8:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_8<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_16:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_16<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_64:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_64<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_128:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_128<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_256:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_256<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			case AHB_CLOCK_DIVIDED_BY_512:
				local_CFGRregister  = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_AHB;
				local_CFGRregister |= (AHB_CLOCK_DIVIDED_BY_512<SHIFT_AHB);
				RCC_CFGR = local_CFGRregister;
				break;

				/* ERROR : NOT A CORRECT CHOICE */
			default:
				Return_errorstatus = RCC_NotOK;
				break;

			}
			return Return_errorstatus ;
		}

		//====================================================================================================================================================//

		Rcc_enuErrorStatus  RCC_enuControlPrescalerAPB1(u32 Copy_APB1Prescaler)
		{
			Rcc_enuErrorStatus Return_errorstatus;
			u32 local_CFGRregister;

			switch (Copy_APB1Prescaler)
			{
			case APB1_NO_CLOCK_FACTOR:
			{
				local_CFGRregister  = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB1;
				local_CFGRregister |= (APB1_NO_CLOCK_FACTOR<SHIFT_APB1);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			/* DIVIDED BY 2 */
			case AHB_CLOCK_DIVIDED_BY_2:
			{
				local_CFGRregister  = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB1;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_2<SHIFT_APB1);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			/* DIVIDED BY 4 */
			case AHB_CLOCK_DIVIDED_BY_4:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB1;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_4<SHIFT_APB1);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			/* DIVIDED BY 8 */
			case AHB_CLOCK_DIVIDED_BY_8:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB1;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_8<SHIFT_APB1);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			/* DIVIDED BY 16 */
			case AHB_CLOCK_DIVIDED_BY_16:
			{
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB1;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_16<SHIFT_APB1);
				RCC_CFGR = local_CFGRregister;
				break;
			}
			default:
				Return_errorstatus = RCC_NotOK;
				break;
			}


			return Return_errorstatus;
		}


		//====================================================================================================================================================//

		Rcc_enuErrorStatus  RCC_enuControlPrescalerAPB2(u32 Copy_APB2Prescaler)
		{
			Rcc_enuErrorStatus Return_errorstatus;
			u32 local_CFGRregister;

			switch(Copy_APB2Prescaler)
			{
			case APB1_NO_CLOCK_FACTOR:
				local_CFGRregister  = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB2;
				local_CFGRregister |= (APB1_NO_CLOCK_FACTOR<SHIFT_APB2);
				RCC_CFGR = local_CFGRregister;
				break;

				/* DIVIDED BY 2 */
			case AHB_CLOCK_DIVIDED_BY_2:
				local_CFGRregister  = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB2;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_2<SHIFT_APB2);
				RCC_CFGR = local_CFGRregister;
				break;
				/* DIVIDED BY 4 */
			case AHB_CLOCK_DIVIDED_BY_4:
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB2;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_4<SHIFT_APB2);
				RCC_CFGR = local_CFGRregister;
				break;

				/* DIVIDED BY 8 */
			case AHB_CLOCK_DIVIDED_BY_8:
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB2;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_8<SHIFT_APB2);
				RCC_CFGR = local_CFGRregister;
				break;

				/* DIVIDED BY 16 */
			case AHB_CLOCK_DIVIDED_BY_16:
				local_CFGRregister = RCC_CFGR;
				local_CFGRregister &= ~MASK_SET_PRE_APB2;
				local_CFGRregister |= (APB1_CLOCK_DIVIDED_BY_16<SHIFT_APB2);
				RCC_CFGR = local_CFGRregister;
				break;

			default:
				Return_errorstatus = RCC_NotOK;
				break;
			}


			return Return_errorstatus;
		}

		//====================================================================================================================================================//


		Rcc_enuErrorStatus  RCC_enuEnablePreipheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral)
		{

			Rcc_enuErrorStatus Ret_enuErrorStatus = RCC_OK;

			/* SELECT BUS */
			switch(Copy_u32PeripheralBus)
			{

			/* AHB1 BUS */
			case AHB1_BUS:
				RCC_AHB1ENR |= (1<<Copy_u32Peripheral);
				break;

				/* AHB2 BUS */
			case AHB2_BUS:
				RCC_AHB2ENR |= (1<<Copy_u32Peripheral);
				break;

				/* APB1 BUS */
			case APB1_BUS:
				RCC_APB1ENR |= (1<<Copy_u32Peripheral);
				break;

				/* APB2 BUS */
			case APB2_BUS:
				RCC_APB2ENR |= (1<<Copy_u32Peripheral);
				break;

			default:
				Ret_enuErrorStatus =  RCC_NotOK;
				break;
			}
			return Ret_enuErrorStatus;
		}

		//====================================================================================================================================================//
		Rcc_enuErrorStatus RCC_enuDisablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral)
		{
			Rcc_enuErrorStatus Ret_enuErrorStatus = RCC_OK;

			/* Check if Copy_u32PeripheralBus is within the expected range */
			if ((Copy_u32PeripheralBus != AHB1_BUS) && (Copy_u32PeripheralBus != AHB2_BUS) &&
					(Copy_u32PeripheralBus != APB1_BUS) && (Copy_u32PeripheralBus != APB2_BUS))
			{
				Ret_enuErrorStatus = RCC_NotOK;
			}
			else
			{
				/* SELECT BUS */
				switch (Copy_u32PeripheralBus)
				{
				/* AHB1 BUS */
				case AHB1_BUS:
					RCC_AHB1ENR &= (~(1 << Copy_u32Peripheral));
					break;

					/* AHB2 BUS */
				case AHB2_BUS:
					RCC_AHB2ENR &= (~(1 << Copy_u32Peripheral));
					break;

					/* APB1 BUS */
				case APB1_BUS:
					RCC_APB1ENR &= (~(1 << Copy_u32Peripheral));
					break;

					/* APB2 BUS */
				case APB2_BUS:
					RCC_APB2ENR &= (~(1 << Copy_u32Peripheral));
					break;

				default:
					Ret_enuErrorStatus = RCC_NotOK;
					break;
				}
			}
			return Ret_enuErrorStatus;
		}

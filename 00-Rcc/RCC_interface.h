/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Ahmed Adel Abdalla
 *  Date    : 5/2/2024
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */


/**************************************************************************/
/*    - What i sell To customer ?                                         */
/*               * The Architect Give The APIs                            */
/*                          1-  The Name of Function                      */
/*                          2-  what is the input                         */
/*                          3-  Return Type                               */
/*                          4-  Object Like Macros                        */
/**************************************************************************/


/**************************************************************************/
/*                    Guard for calling one time in .c files              */
/**************************************************************************/


#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/**************************************************************************/
/*                          Struct Types                               */
/**************************************************************************/

typedef enum
{
	Rcc_OK = 10,
	Rcc_InputError,
	Rcc_ClockNotReady,
	Rcc_PllEnable,
	Rcc_InputRangeError
}Rcc_tenuErrorStatus;

typedef enum
{
	Rcc_HsiClockSytem = 0,
	Rcc_HseClockSytem,
	Rcc_PllClockSytem

}Rcc_tenuClockSystem;



/**************************************************************************/
/*                          Define BUS Name                               */
/**************************************************************************/

typedef enum
{
	RCC_AHB1 = 0 ,
	RCC_AHB2     ,
	RCC_APB1     ,
	RCC_APB2     ,
    RCC_INVALID_BUS
}RCC_uddtBusName;



/**************************************************************************/
/*                          Define RCC AHB1 CLK Enable                    */
/**************************************************************************/

#define RCC_GPIOA_EN      0U
#define RCC_GPIOB_EN      1U
#define RCC_GPIOC_EN      2U
#define RCC_GPIOD_EN      3U
#define RCC_DMA1_EN       21U
#define RCC_DMA2_EN       22U



/**************************************************************************/
/*                          Define RCC AHB2 CLK Enable                    */
/**************************************************************************/
#define RCC_OTGFS_EN      7U


/**************************************************************************/
/*                          Define RCC APB1 CLK Enable                    */
/**************************************************************************/
#define RCC_TIM2_EN      0U
#define RCC_TIM3_EN      1U
#define RCC_TIM4_EN      2U
#define RCC_TIM5_EN      3U
#define RCC_WWDG_EN      11U
#define RCC_SPI2_EN      14U
#define RCC_SPI3_EN      15U
#define RCC_USART2_EN    17U
#define RCC_I2C1_EN      21U
#define RCC_I2C2_EN      22U
#define RCC_I2C3_EN      23U
#define RCC_PWR_EN       28U


/**************************************************************************/
/*                          Define RCC APB2 CLK Enable                    */
/**************************************************************************/
#define RCC_TIM1_EN      0U
#define RCC_USART1_EN    4U
#define RCC_USART6_EN    5U
#define RCC_ADC1_EN      8U
#define RCC_SDIO_EN      11U
#define RCC_SPI1_EN      12U
#define RCC_SPI4_EN      13U
#define RCC_SYSCFG_EN    14U
#define RCC_TIM9_EN      16U
#define RCC_TIM10_EN     17U
#define RCC_TIM11_EN     18U





/**************************************************************************/
/*                          Function Prototypes                           */
/**************************************************************************/

/*
 * Public Function:		Rcc_SetClockOn
 * Input Parameter:		Copy_u8ClockSelection in range {HSI_CLOCK, HSEON_CLOCK, PLLON_CLOCK}
 *
 * Description:			This function to set the clock system
 *
 * Return:				Error Input if it's not from the range
 *
 * */

Rcc_tenuErrorStatus Rcc_SetClockOn(u32 Copy_u32ClockSelection);


/*
 * Public Function:		Rcc_ReadStatusClock
 * Input Parameter:		Copy_u8ClockSelection in range {HSI_CLOCK, HSEON_CLOCK, PLLON_CLOCK}
 *
 * Description:			This function is to read the status of the clock set ready or not
 *
 * Return:				-> If the clock fail to be ready will return Error Status
 *						-> if the input not in range
 * */

Rcc_tenuErrorStatus	Rcc_ReadStatusClock(u32 Copy_u32ClockSelection);


/*
 * Public Function  		:	Rcc_SetHseClockBypass
 * Description				:	This Function is to set the bypass clock to bypass the oscillator with an external clock
 *
 *!!!Constrain				:	You can only set it if and only if the you didn't set the clock system
 *
 * Input Parameter			:	Not-Applicable	(void)
 *
 * Return					:	Not-Applicable (void)
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

void Rcc_SetHseClockBypass(void);


/*
 * Public Function  		:	Rcc_SetPllClock
 * Description				:	This Function is to set the PLL clock
 *
 *!!!Constrain				:	you need to set the clock before configure the PLL
 *
 * Input Parameter:			:	Copy_u8ClockSelection in range {PLL_HSI, PLL_HSE}
 *
 * Return					:	-> Wrong Input
 * 								-> The PLL in ON
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus Rcc_SetPllClock(u32 Copy_u32ClockSelection);


/*
 * Public Function  		:	Rcc_PllConfigureation
 * Description				:	This Function is to set the bypass clock to bypass the oscillator with an external clock
 *
 *!!!Constrain				:	You can only configure the PLL if the PLL is disable
 *
 *Input Parameter			:	@ Copy_u8PllM in range (2 -> 63)
 * 								@ Copy_u8PllN in range (192 -> 432)
 * 								@ Copy_u8PllQ in range (2 -> 15)
 * 								@ Copy_u8PllP in range that the output clock does not exceed 84 MHZ
 *
 *!!Attention				:	The default clock is HSI in case you didn't set PLL Clock
 *
 * Return					:	Input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_PllConfiguration(u8 Copy_u8PllM, u16 Copy_u16PllN, u8 Copy_u8PllQ, u8 Copy_u8PllP);


/*
 * Public Function			:	Rcc_SetClockSystem
 *
 * Description				:	This function to set the clock system that will feed the processor
 * 								& peripheral...
 *
 * Input Parameter			:	Copy_u8ClockSlection in range (HSI_CLOCK_SYSTEM, HSE_CLOCK_SYSTEM, PLL_CLOCK_SYSTEM)
 *
 * Return 					: 	Error Status if the input out of range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_SetClockSystem (u32 Copy_u32ClockSlection);



/*
 * Public Function:		Rcc_ReadSystemClockStatus
 * Input Parameter:		Copy_u8ClockSelection in range {HSI_CLOCK, HSEON_CLOCK, PLLON_CLOCK}
 *
 * Description:			This function is to read the status of the system clock
 *
 * Return:				-> the clock of the system
 *
 * */

Rcc_tenuClockSystem Rcc_ReadSystemClockStatus (void);


/*
 * Public Function			:	Rcc_ResetAHB1Peripheral
 *
 * Description				:	This function is to reset the AHB1 peripheral (it disable the clock)
 *
 * Input Parameter			:	Copy_u8AHB1Peripheral in range
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *
 * Return 					: 	Error Status if the input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_ResetAHB1Peripheral(u32 Copy_u32AHB1Peripheral);


/*
 * Public Function			:	Rcc_ResetAPB1Peripheral
 *
 * Description				:	This function is to reset the ApB1 peripheral (it disable the clock)
 *
 * Input Parameter			:	u8 Copy_u8APB2Peripheral in range {}
 *
 * Return 					: 	Error Status if the input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_ResetAPB1Peripheral(u32 Copy_u32APB1Peripheral);


/*
 * Public Function			:	Rcc_ResetAPB2Peripheral
 *
 * Description				:	This function is to reset the APB2 peripheral (it disable the clock)
 *
 * Input Parameter			:	u8 Copy_u8APB2Peripheral in range {}
 *
 * Return 					: 	Error Status if the input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_ResetAPB2Peripheral(u32 Copy_u32APB2Peripheral);


/*
 * Public Function			:	Rcc_SetAHB1Peripheral
 *
 * Description				:	This function is to reset the AHB1 peripheral (it disable the clock)
 *
 * Input Parameter			:	Copy_u8AHB1Peripheral in range
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *								@ SET_RESET_GPIO
 *
 * Return 					: 	Error Status if the input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_SetAHB1Peripheral(u32 Copy_u32AHB1Peripheral);


/*
 * Public Function			:	Rcc_SetAPB1Peripheral
 *
 * Description				:	This function is to reset the ApB1 peripheral (it disable the clock)
 *
 * Input Parameter			:	u8 Copy_u8APB2Peripheral in range
 *
 *
 * Return 					: 	Error Status if the input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *

 * */

Rcc_tenuErrorStatus	Rcc_SetAPB1Peripheral(u32 Copy_u32APB1Peripheral);


/*
 * Public Function			:	Rcc_SetAPB2Peripheral
 *
 * Description				:	This function is to reset the APB2 peripheral (it disable the clock)
 *
 * Input Parameter			:	u8 Copy_u8APB2Peripheral in range {}
 *
 * Return 					: 	Error Status if the input not in range
 *
 * Input/Output Parameter	:	Not-Applicable
 *
 * */

Rcc_tenuErrorStatus	Rcc_SetAPB2Peripheral(u32 Copy_u32APB2Peripheral);

                                                      ;

#endif /* MRCC_INTERFACE_H_ */

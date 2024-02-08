/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Ahmed Adel Abdalla
 *  Date    : 5/2/2024
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

//==============================================================================================================



/******************************************************************************/
/*                              Register Definitions                          */
/*----------------------------------------------------------------------------*/
/*    - Developer can't edit in it                                            */
/*    - Design :                                                              */
/*                         -   #define        : YES                           */
/*                         -   Struct         : NO                            */
/*                         -   Union          : NO                            */
/******************************************************************************/

/******************************************************************************/
/*              Object Like Macro For RCC Base Address Registers              */
/******************************************************************************/

#define RCC_BASE_ADDRESS 0x40023800

/******************************************************************************/
/*                         Macros of RCC Register Map                         */
/******************************************************************************/

#define RCC_CR                             (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x00)))
#define RCC_PLLCFGR                        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x04)))
#define RCC_CFGR                           (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x08)))
#define RCC_CIR                            (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x0C)))
#define RCC_AHB1RSTR                       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x10)))
#define RCC_AHB2RSTR                       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x14)))
#define RCC_APB1RSTR                       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x20)))
#define RCC_APB2RSTR                       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x24)))
#define RCC_AHB1ENR                        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x30)))
#define RCC_AHB2ENR                        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x34)))
#define RCC_APB1ENR                        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x40)))
#define RCC_APB2ENR                        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x44)))
#define RCC_AHB1LPENR                      (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x50)))
#define RCC_AHB2LPENR                      (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x54)))
#define RCC_APB1LPENR                      (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x60)))
#define RCC_APB2LPENR                      (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x64)))
#define RCC_BDCR                           (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x70)))
#define RCC_CSR                            (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x74)))
#define RCC_SSCGR                          (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x80)))
#define RCC_PLLI2SCFGR                     (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x84)))
#define RCC_DCKCFGR                        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x8C)))


/******************************************************************************/
/*                          Clock Source Options                              */
/******************************************************************************/

/*-----------------------------------------DEFINE-------------------------------------------*/

/*Parameter to be used for function :
 * @	Rcc_SetClockON
 * @	Rcc_ReadStatusClock
 * */
#define HSI_CLOCK	0x10000001
#define HSE_CLOCK	0x10010000
#define PLL_CLOCK	0x11000000

/*Parameter to be used for function:
 * @	Rcc_SetPllClock
 * */
#define PLL_HSI		0x20000000
#define PLL_HSE		0x20400000

/*Parameter to be used for function:
 * @	Rcc_SetClockSystem
 * */
#define HSI_CLOCK_SYSTEM	0x30000000
#define HSE_CLOCK_SYSTEM	0x30000001
#define PLL_CLOCK_SYSTEM	0x30000002

/*Parameter to be used for function:
 * @	Rcc_ReadClockSystemStatus
 * */
#define HSI_CLOCK_SYSTEM_STATUS		0x00000000
#define HSE_CLOCK_SYSTEM_STATUS		0x00000004
#define PLL_CLOCK_SYSTEM_STATUS		0x00000008

/*Parameter to be used for function:
 * @	Rcc_ResetAHB1Peripheral
 * @	Rcc_SetAHB1Peripheral
 * */
#define SET_RESET_GPIOA			0x40000001
#define SET_RESET_GPIOB			0x40000002
#define SET_RESET_GPIOC			0x40000004
#define SET_RESET_GPIOD			0x40000008
#define SET_RESET_GPIOE			0x40000010
#define SET_RESET_GPIOH			0x40000080

/*Parameter to be used for function:
 * @	Rcc_ResetAPB2Peripheral
 * @	Rcc_SetAPB2Peripheral
 * */
#define SET_RESET_TIM1			0x50000001
#define SET_RESET_USART1		0x50000010
#define SET_RESET_USART6		0x50000020
#define SET_RESET_ADC1			0x50000100
#define SET_RESET_SDIO			0x50000800
#define SET_RESET_SPI1			0x50001000
#define SET_RESET_SPI4			0x50002000
#define SET_RESET_SYSTEMCFGR	0x50004000
#define SET_RESET_TIM9			0x50100000
#define SET_RESET_TIM10			0x50200000
#define SET_RESET_TIM11			0x50400000

/*Parameter to be used for function:
 * @	Rcc_ResetAPB1Peripheral
 * @	Rcc_SetAPB1Peripheral
 * */
#define SET_RESET_TIM2			0x60000001
#define SET_RESET_TIM3			0x60000002
#define SET_RESET_TIM4			0x60000004
#define SET_RESET_TIM5			0x60000008
#define SET_RESET_WWDG			0x60000800
#define SET_RESET_SPI2			0x60004000
#define SET_RESET_SPI3			0x60008000
#define SET_RESET_USART2		0x60020000
#define SET_RESET_I2C1			0x60200000
#define SET_RESET_I2C2			0x60400000
#define SET_RESET_I2C3			0x60800000


#endif /* MRCC_PRIVATE_H_ */

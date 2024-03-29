/*
 ============================================================================
 Name        : NVIC.h
 Author      : Ahmed Adel
 Description : Header File for the NVIC Driver
 Date        : 5/3/2024
 ============================================================================
 */

#ifndef NVIC_H_
#define NVIC_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "STD_TYPES.h"


/******************************Types**************************************8*************/


typedef enum{
	NVIC_OK,
	NVIC_INVAILD_INT_NUMBER,
	NVIC_INVAILD_GROUP_NUMBER,
	NVIC_NULL_POINTER,
	NVIC_INVAILD_Priority

}NVIC_ERRORSTATE_t;




/*##########################Defines#####################################*/


#define NVIC_PRIORITYGROUP_16_NONE    (0x0UL << 8)  // None bits group, 16 bits sub priority
#define NVIC_PRIORITYGROUP_8_2        (0x4UL << 8)  // 8 bits group, 2 bits sub priority
#define NVIC_PRIORITYGROUP_4_4        (0x5UL << 8)  // 4 bits group, 4 bits sub priority
#define NVIC_PRIORITYGROUP_2_8        (0x6UL << 8)  // 2 bits group, 8 bits sub priority
#define NVIC_PRIORITYGROUP_NONE_16    (0x7UL << 8)  // None bits group, 16 bits sub priority


#define NVIC_WINDOW_WATCHDOG_TIMER		0
#define	NIVC_EXTERNAL_LINE16			1
#define	NIVC_EXTERNAL_LINE21			2
#define	NIVC_EXTERNAL_LINE22			3
#define	NIVC_FLASH_INTERRUPT			4
#define	NVIC_RCC_INTERRUPT				5
#define NVIC_EXT0_INTERRRUPT			6
#define NVIC_EXT1_INTERRRUPT			7
#define NVIC_EXT2_INTERRRUPT			8
#define NVIC_EXT3_INTERRRUPT			9
#define NVIC_EXT4_INTERRRUPT			10
#define NVIC_DMA1_STREAM0				11
#define NVIC_DMA1_STREAM1				12
#define NVIC_DMA1_STREAM2				13
#define NVIC_DMA1_STREAM3				14
#define NVIC_DMA1_STREAM4				15
#define NVIC_DMA1_STREAM5				16
#define NVIC_DMA1_STREAM6               17
#define NVIC_ADC_INTERRUPT              18
#define NVIC_EXT9_INTERRUPT             23
#define NVIC_TIM1_BRK_INTERRUPT         24
#define NVIC_TIM1_UP_INTERRUPT          25
#define NVIC_TIMI1_TRG_INTERRUPT        26
#define NVIC_TIMI1_CC_INTERRUPT         27
#define NVIC_TIMI2_INTERRUPT            28
#define NVIC_TIMI3_INTERRUPT            29
#define NVIC_TIMI4_INTERRUPT            30
#define NVIC_I2C1_EV_INTERRUPT          31
#define NVIC_I2C1_ER_INTERRUPT          32
#define NVIC_I2C2_EV_INTERRUPT          33
#define NVIC_I2C2_ER_INTERRUPT          34
#define NVIC_SPI1_INTERRUPT             35
#define NVIC_SPI2_INTERRUPT             36
#define NVIC_USART1_INTERRUPT           37
#define NVIC_USART2_INTERRUPT           38
#define NVIC_EXTI15_INTERRUPT           40
#define NVIC_EXTI17_INTERRUPT           41
#define NVIC_EXTI18_INTERRUPT           42
#define NVIC_DMA1_INTERRUPT             47
#define NVIC_SDIO_INTERRUPT             49
#define NVIC_TIM5_INTERRUPT             50
#define NVIC_SPI3_INTERRUPT             51
#define NVIC_DMA2_STREAM0_INTERRUPT     56
#define NVIC_DMA2_STREAM1_INTERRUPT     57
#define NVIC_DMA2_STREAM2_INTERRUPT     58
#define NVIC_DMA2_STREAM3_INTERRUPT     59
#define NVIC_DMA2_STREAM4_INTERRUPT     60
#define NVIC_OTG_FS_INTERRUPT           67
#define NVIC_DMA2_STREAM5_INTERRUPT     68
#define NVIC_DMA2_STREAM6_INTERRUPT     69
#define NVIC_DMA2_STREAM7_INTERRUPT     70
#define NVIC_USART6_INTERRUPT           71
#define NVIC_I2C3_EV_INTERRUPT          72
#define NVIC_I2C3_ER_INTERRUPT          73
#define NVIC_FPU_INTERRUPT              81
#define NVIC_SPI4_INTERRUPT             84

#define NVIC_TotalInterrputs            240
#define AIRCR_Clear                  0xFFFFF8FF
//===================================Locations========================================//
#define SCB_AIRCR    *((volatile u32 *)0xE000ED00+0x0C)

#define NVIC_ISER_BASE ((volatile u32 *) 0xE000E100)
#define NVIC_ICER_BASE ((volatile u32 *) 0xE000E180)
#define NVIC_ISPR_BASE ((volatile u32 *) 0xE000E200)
#define NVIC_ICPR_BASE ((volatile u32 *) 0xE000E280)
#define NVIC_IAB_BASE  ((volatile u32 *) 0xE000E300)
#define NVIC_IPR_BASE  ((volatile u32 *) 0xE000E400)
#define NVIC_STIR      ((volatile u32 *) 0xE000EF00)



/*******************************************************************************
 *                  	    Functions Prototypes                               *
//================================================================================//
 *
 */




NVIC_ERRORSTATE_t  NVIC_EnableInterrupt (u8 Copy_InterrputID);

NVIC_ERRORSTATE_t  NVIC_DisableInterrupt (u8 Copy_InterrputID);

NVIC_ERRORSTATE_t  NVIC_SetPending (u8 Copy_InterrputID);

NVIC_ERRORSTATE_t  NVIC_ClearPending (u8 Copy_InterrputID);

NVIC_ERRORSTATE_t  NVIC_GetActiveState (u8 Copy_InterrputID, u8* Active_value);

NVIC_ERRORSTATE_t NVIC_SetPriority (u8 Copy_InterrputID , u8 Copy_priority);

NVIC_ERRORSTATE_t NVIC_SetSubPriority (u8 Group_Number );

NVIC_ERRORSTATE_t NVIC_SetSoftwareInterrput (u8 Copy_InterrputID);


#endif /* NVIC_H_ */

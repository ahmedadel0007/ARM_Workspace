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

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* ==================================================================== */
/* ======================== Registers Defination ====================== */
/* ==================================================================== */
#define RCC_CR                  *((volatile u32*)0x40023800)
#define RCC_PLLCFGR             *((volatile u32*)0x40023804)
#define RCC_CFGR                *((volatile u32*)0x40023808)
#define RCC_CIR                 *((volatile u32*)0x4002380C)
#define RCC_AHB1RSTR            *((volatile u32*)0x40023810)
#define RCC_AHB2RSTR            *((volatile u32*)0x40023814)
#define RCC_APB1RSTR            *((volatile u32*)0x40023820)
#define RCC_APB2RSTR            *((volatile u32*)0x40023824)
#define RCC_AHB1ENR             *((volatile u32*)0x40023830)
#define RCC_AHB2ENR             *((volatile u32*)0x40023834)
#define RCC_APB1ENR             *((volatile u32*)0x40023840)
#define RCC_APB2ENR             *((volatile u32*)0x40023844)
#define RCC_AHB1LPENR           *((volatile u32*)0x40023850)
#define RCC_AHB2LPENR           *((volatile u32*)0x40023854)
#define RCC_APB1LPENR           *((volatile u32*)0x40023860)
#define RCC_APB2LPENR           *((volatile u32*)0x40023864)
#define RCC_BDCR                *((volatile u32*)0x40023870)
#define RCC_CSR                 *((volatile u32*)0x40023874)
#define RCC_SSCGR               *((volatile u32*)0x40023880)
#define RCC_PLLI2SCFGR          *((volatile u32*)0x40023884)
#define RCC_DCKCFGR             *((volatile u32*)0x4002388C)

/*
typedef struct{
volatile	u32 CR;

}RCC_Pointer_t;*/


/* ==================================================================== */
/* ========================== Clock Types ============================= */
/* ==================================================================== */
#define RCC_HSI                 0
#define RCC_HSE                 1
#define RCC_PLL                 2

/* ==================================================================== */
/* ============================= Masks ================================ */
/* ==================================================================== */
#define RCC_SET_CFGR_HSI         0x00000003
#define RCC_SET_CR_HSI           0x00000001

#define RCC_GET_HSI_RDY          0x00000002
#define RCC_GET_HSE_RDY          0x00020000
#define RCC_GET_PLL_RDY          0x02000000

#define MASK_GET_SYSCLK          0x0000000C
#define MASK_SET_HSI             0x00000001
#define MASK_SET_HSE             0x00010000
#define MASK_SET_PLL             0x01000000

#define MASK_GET_RDY_HSI         0x00000002
#define MASK_GET_RDY_HSE         0x00020000
#define MASK_GET_RDY_PLL         0x02000000
#define MASK_GET_ON_PLL          0x01000000

#define MASK_SET_PPL_M           0x0000003F
#define MASK_SET_PPL_N           0x00007FC0
#define MASK_SET_PPL_P           0x00030000
#define MASK_SET_PPL_Q           0x0F000000
#define MASK_SET_PPL_SRC         0x00400000

#define SHIFT_PLL_M              0
#define SHIFT_PLL_N              6
#define SHIFT_PLL_P              16
#define SHIFT_PLL_Q              24
#define SHIFT_PLL_SRC            22

#define SHIFT_AHB                4
#define SHIFT_APB1               10
#define SHIFT_APB2               13

#define MASK_SET_PRE_AHB         0x000000F0
#define MASK_SET_PRE_APB1        0x00001C00
#define MASK_SET_PRE_APB2        0x0000E000

#define  MASK_HSI_ON             0x00000001
#define  MASK_HSI_RDY            0x00000002
#define  MASK_HSE_ON             0x00010000
#define  MASK_HSE_RDY            0x00020000
#define  MASK_PLL_ON             0x01000000
#define  MASK_PLL_RDY            0x02000000

#define  MASK_SW                 0x00000003
#define  MASK_GET_SWS            0x0000000C

#define MASK_SWS_HSI 			 0x00000000
#define MASK_SWS_HSE 			 0x00000004
#define MASK_SWS_PLL 			 0x00000008

#define RCC_NOT_RDY_STATUS 		 0
#define RCC_RDY_STATUS 			 1

/* ========================== AHB Prescalers ========================== */
#define AHB_NO_CLOCK_FACTOR                           0b0000
#define AHB_CLOCK_DIVIDED_BY_2                        0b1000
#define AHB_CLOCK_DIVIDED_BY_4                        0b1001
#define AHB_CLOCK_DIVIDED_BY_8                        0b1010
#define AHB_CLOCK_DIVIDED_BY_16                       0b1011
#define AHB_CLOCK_DIVIDED_BY_64                       0b1100
#define AHB_CLOCK_DIVIDED_BY_128                      0b1101
#define AHB_CLOCK_DIVIDED_BY_256                      0b1110
#define AHB_CLOCK_DIVIDED_BY_512                      0b1111

/* ========================== AHB Prescalers ========================== */
#define APB1_NO_CLOCK_FACTOR                           0b000
#define APB1_CLOCK_DIVIDED_BY_2                        0b100
#define APB1_CLOCK_DIVIDED_BY_4                        0b101
#define APB1_CLOCK_DIVIDED_BY_8                        0b110
#define APB1_CLOCK_DIVIDED_BY_16                       0b111

/* ========================== APB2 Prescaler ========================== */
#define APB2_NO_CLOCK_FACTOR                           0b000
#define APB2_CLOCK_DIVIDED_BY_2                        0b100
#define APB2_CLOCK_DIVIDED_BY_4                        0b101
#define APB2_CLOCK_DIVIDED_BY_8                        0b110
#define APB2_CLOCK_DIVIDED_BY_16                       0b111

/* ============================ Pins Masks ============================= */
#define MASK_PIN_0                      0x00000001
#define MASK_PIN_1                      0x00000002
#define MASK_PIN_2                      0x00000004
#define MASK_PIN_3                      0x00000008

#define MASK_PIN_4                      0x00000010
#define MASK_PIN_5                      0x00000020
#define MASK_PIN_6                      0x00000040
#define MASK_PIN_7                      0x00000080

#define MASK_PIN_8                      0x00000100
#define MASK_PIN_9                      0x00000200
#define MASK_PIN_10                     0x00000400
#define MASK_PIN_11                     0x00000800

#define MASK_PIN_12                     0x00001000
#define MASK_PIN_13                     0x00002000
#define MASK_PIN_14                     0x00004000
#define MASK_PIN_15                     0x00008000

#define MASK_PIN_16                     0x00010000
#define MASK_PIN_17                     0x00020000
#define MASK_PIN_18                     0x00040000
#define MASK_PIN_19                     0x00080000

#define MASK_PIN_20                     0x00100000
#define MASK_PIN_21                     0x00200000
#define MASK_PIN_22                     0x00400000
#define MASK_PIN_23                     0x00800000

#define MASK_PIN_24                     0x01000000
#define MASK_PIN_25                     0x02000000
#define MASK_PIN_26                     0x04000000
#define MASK_PIN_27                     0x08000000

#define MASK_PIN_28                     0x10000000
#define MASK_PIN_29                     0x20000000
#define MASK_PIN_30                     0x40000000
#define MASK_PIN_31                     0x80000000


/* ==================================================================== */
/* =========================== Peripherals ============================ */
/* ==================================================================== */

/* ================================ AHB1 ============================== */
#define GPIOA_RCC                       0
#define GPIOB_RCC                       1
#define GPIOC_RCC                       2
#define GPIOD_RCC                       3
#define GPIOE_RCC                       4
#define GPIOH_RCC                       7
#define CRC_RCC                         12
#define DMA1_RCC                        21
#define DMA2_RCC                        22

/* ================================ AHB2 ============================== */
#define OTGFS_RCC 7

/* ================================ APB1 ============================== */
#define TIM2_RCC                        0
#define TIM3_RCC                        1
#define TIM4_RCC                        2
#define TIM5_RCC                        3
#define WWDG_RCC                        11
#define SPI2_RCC                        14
#define SPI3_RCC                        15
#define USART2_RCC                      17
#define I2C1_RCC                        21
#define I2C2_RCC                        22
#define I2C3_RCC                        23
#define PWR_RCC                         28

/* ================================ APB2 ============================== */
#define TIM1_RCC                        0
#define USART1_RCC                      4
#define USART6_RCC                      5
#define ADC1_RCC                        8
#define SDIO_RCC                        11
#define SPI1_RCC                        12
#define SPI4_RCC                        13
#define SYSCFG_RCC                      14
#define TIM9_RCC                        16
#define TIM10_RCC                       17
#define TIM11_RCC                       18


#define AHB1_BUS                        0
#define AHB2_BUS                        1
#define APB1_BUS                        2
#define APB2_BUS                        3



/* ==================================================================== */
/* ========================== New Types =============================== */
/* ==================================================================== */
typedef enum{
  HSI,
  HSE
}RCC_enuPLLSRC;

typedef struct{
  RCC_enuPLLSRC   RCC_enuPLLSCR;
  u32             RCC_enuPLL_M;
  u32             RCC_enuPLL_N;
  u32             RCC_enuPLL_P;
  u32             RCC_enuPLL_Q;
}RCC_structCLKPLL;

typedef enum {
  RCC_OK,
  RCC_NotOK
}Rcc_enuErrorStatus;

typedef enum{
  OFF,
  ON
}RCC_enuClkStatus;

typedef enum{
  Not_Ready,
  Ready
}RCC_enuReadyStatus;

typedef enum {
  RCC_ClockStatus_HSI,
  RCC_ClockStatus_HSE,
  RCC_ClockStatus_PLL,
  RCC_ClockStatus_NotApplicable
}RCC_enuClockStatus;



/**************************************************************************/
/*                          Function Prototypes                           */
/**************************************************************************/
Rcc_enuErrorStatus	Rcc_SelectsystemClk (u32 Copy_ClockSelection);

Rcc_enuErrorStatus  RCC_ControlClk(u8 Copy_ClockSystem,RCC_enuClkStatus Copy_enuClkStatus);

Rcc_enuErrorStatus  RCC_enuCheckReady(u8 Copy_u8ClockSystem, u8* Add_pu8ReadyStatus);

Rcc_enuErrorStatus  RCC_enuConfigPLL(RCC_structCLKPLL Copy_structPLLCongif);

Rcc_enuErrorStatus  RCC_enuControlPrescalerAHB(u32 Copy_AHBPrescaler);

Rcc_enuErrorStatus  RCC_enuControlPrescalerAPB1(u32 Copy_APB1Prescaler);

Rcc_enuErrorStatus  RCC_enuControlPrescalerAPB2(u32 Copy_APB2Prescaler);

Rcc_enuErrorStatus  RCC_enuEnablePreipheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);

Rcc_enuErrorStatus RCC_enuDisablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);



#endif /* MRCC_INTERFACE_H_ */

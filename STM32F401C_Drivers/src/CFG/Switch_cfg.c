
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "GPIO.h"
#include "Switch_cfg.h"
#include "Switch.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/********************Macros for the HSwitch Ports********************/
#define HSwitch_PORTA  	(void *)(0x40020000)
#define HSwitch_PORTB	(void *)(0x40020400)
#define HSwitch_PORTC  	(void *)(0x40020800)
#define HSwitch_PORTD 	(void *)(0x40020C00)
#define HSwitch_PORTE 	(void *)(0x40021000)
#define HSwitch_PORTH	(void *)(0x40021C00)

/********************Macros for the HSwitch Pins********************/
#define HSwitch_PIN0 	0x00000000
#define HSwitch_PIN1 	0x00000001
#define HSwitch_PIN2 	0x00000002
#define HSwitch_PIN3 	0x00000003
#define HSwitch_PIN4 	0x00000004
#define HSwitch_PIN5 	0x00000005
#define HSwitch_PIN6 	0x00000006
#define HSwitch_PIN7 	0x00000007
#define HSwitch_PIN8 	0x00000008
#define HSwitch_PIN9	0x00000009
#define HSwitch_PIN10 	0x0000000A
#define HSwitch_PIN11 	0x0000000B
#define HSwitch_PIN12 	0x0000000C
#define HSwitch_PIN13 	0x0000000D
#define HSwitch_PIN14 	0x0000000E
#define HSwitch_PIN15 	0x0000000F
/********************Macros for the HSwitch type of connection********************/
#define HSwitch_INPUT_FL					0x00000000
#define HSwitch_INPUT_PL					0x00000008
#define HSwitch_INPUT_PD					0x00000010
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set HSwitchs configuration
 I make an extra extern here beacuse of linker issue when declare and constant global array 
 It implicitly make it static fri this file so the other files can't see it */
const Switch_cfg_t SWITCHEs[_Switch_Num] = {
   /*Ex : Set HSwitch1 Configuration*/
    [Switch_mode] = {
        .Pin = HSwitch_PIN7,
        .Port = GPIO_A,
        .State = GPIO_MODE_INPUT_PU
    },
   [Switch_up] = {
        .Pin = HSwitch_PIN1,
        .Port = HSwitch_PORTA,
        .State = HSwitch_INPUT_PL
    },
   [Switch_down] = {
        .Pin = HSwitch_PIN14,
        .Port = HSwitch_PORTB,
        .State = HSwitch_INPUT_PL
    },	

};
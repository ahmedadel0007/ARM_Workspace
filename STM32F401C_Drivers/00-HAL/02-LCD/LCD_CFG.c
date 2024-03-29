/************************************************************************************************************************************************/
/* File             :       LCD_CFG.c                                                                                                        */
/* AUTHOR           :       Ahmed Adel                                                                                                       */
/* Origin Date      :       3/26/2024                                                                                                            */
/* SWC              :       Character LCD                                                                                                       */
/************************************************************************************************************************************************/
#include"LCD.h"
#include"LCD_CFG.h"
#include"GPIO.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/********************Macros for the LCD Ports********************************/
#define LCD_PORTA  	(void *)(0x40020000)
#define LCD_PORTB	(void *)(0x40020400)
#define LCD_PORTC  	(void *)(0x40020800)
#define LCD_PORTD 	(void *)(0x40020C00)
#define LCD_PORTE 	(void *)(0x40021000)
#define LCD_PORTH	(void *)(0x40021C00)

/********************Macros for the LCD Pins*****************************/
#define LCD_PIN0 	0x00000000
#define LCD_PIN1 	0x00000001
#define LCD_PIN2 	0x00000002
#define LCD_PIN3 	0x00000003
#define LCD_PIN4 	0x00000004
#define LCD_PIN5 	0x00000005
#define LCD_PIN6 	0x00000006
#define LCD_PIN7 	0x00000007
#define LCD_PIN8 	0x00000008
#define LCD_PIN9	0x00000009
#define LCD_PIN10 	0x0000000A
#define LCD_PIN11 	0x0000000B
#define LCD_PIN12 	0x0000000C
#define LCD_PIN13 	0x0000000D
#define LCD_PIN14 	0x0000000E
#define LCD_PIN15 	0x0000000F

const LCD_CFG_t LCDs [_LCD_PIN_NUMNER]={

		[D0]={.port=LCD_PORTB ,.pin=LCD_PIN0},
		[D1]={.port=LCD_PORTB ,.pin=LCD_PIN1},
		[D2]={.port=LCD_PORTB ,.pin=LCD_PIN2},
		[D3]={.port=LCD_PORTB ,.pin=LCD_PIN3},
		[D4]={.port=LCD_PORTB ,.pin=LCD_PIN4},
		[D5]={.port=LCD_PORTB ,.pin=LCD_PIN5},
		[D6]={.port=LCD_PORTB ,.pin=LCD_PIN6},
		[D7]={.port=LCD_PORTB ,.pin=LCD_PIN7},
		[RS]={.port=LCD_PORTB ,.pin=LCD_PIN8},
		[RW]={.port=LCD_PORTB ,.pin=LCD_PIN9},
		[En]={.port=LCD_PORTB ,.pin=LCD_PIN10},


};

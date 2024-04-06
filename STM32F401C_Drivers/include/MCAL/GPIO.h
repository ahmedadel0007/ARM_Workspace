/*
 * GPIO.h
 *
 *  Created on: 18, 2024
 *      Author: Ahmed Adel
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"STD_TYPES.h"
#include"BIT_MATH.h"

//============================================================================================================================//

/*** GPIO_Ports Base addresses ***/
#define GPIO_A ((void*)0x40020000)
#define GPIO_B ((void*)0x40020400)
#define GPIO_C ((void*)0x40020800)



/*** GPIO Pins index ***/
#define GPIO_PIN0    0x00000000
#define GPIO_PIN1    0x00000001
#define GPIO_PIN2    0x00000002
#define GPIO_PIN3    0x00000003
#define GPIO_PIN4    0x00000004
#define GPIO_PIN5    0x00000005
#define GPIO_PIN6    0x00000006
#define GPIO_PIN7    0x00000007
#define GPIO_PIN8    0x00000008
#define GPIO_PIN9    0x00000009
#define GPIO_PIN10   0x0000000A
#define GPIO_PIN11   0x0000000B
#define GPIO_PIN12   0x0000000C
#define GPIO_PIN13   0x0000000D
#define GPIO_PIN14   0x0000000E
#define GPIO_PIN15   0x0000000F



#define GPIO_total_pins    15
#define NUMBER_OF_PORTS 	6


/*******Macros for the GPIO pin modes*******/
#define GPIO_MODE_INPUT_FLOATING 	  0x00000000
#define GPIO_MODE_INPUT_PU 	          0x00000004
#define GPIO_MODE_INPUT_PD 	          0x00000008

#define GPIO_MODE_OUTPUT_PP   	0x00000001
#define GPIO_MODE_OUTPUT_PP_PU	0x00000009
#define GPIO_MODE_OUTPUT_PP_PD	0x00000011
#define GPIO_MODE_OUTPUT_OD   	0x00000005
#define GPIO_MODE_OUTPUT_OD_PU	0x0000000D
#define GPIO_MODE_OUTPUT_OD_PD	0x00000015

#define GPIO_MODE_AF_PP    	0x00000002
#define GPIO_MODE_AF_PP_PU 	0x0000000A
#define GPIO_MODE_AF_PP_PD 	0x00000012
#define GPIO_MODE_AF_OD    	0x00000006
#define GPIO_MODE_AF_OD_PU 	0x0000000E
#define GPIO_MODE_AF_OD_PD 	0x00000016

#define GPIO_MODE_ANALOG      	0x00000003

#define GPIO_PIN_NUM 15

#define GPIO_FALSE 0
#define GPIO_TRUE  1

#define GPIO_VALUE_RESET 0
#define GPIO_VALUE_SET 1


#define GPIO_STATE_HIGH  0x00000001
#define GPIO_STATE_LOW    0x00000000
//===============================================================================================================================//

typedef enum {
	GPIO_SPEED_LOW,
	GPIO_SPEED_MEDIUM,
	GPIO_SPEED_HIGH,
	GPIO_SPEED_VERY_HIGH
}
GPIO_Speedstate_t;


typedef struct {
	u8 GPIO_MODE;
	GPIO_Speedstate_t GPIO_SPEED;
	void* GPIO_portnumber;
	u16 GPIO_pinnumber;
}GPIO_Pinconfig_t;

typedef enum {
	GPIO_Nok,
	GPIO_Ok,
	GPIO_Wrong_Port_Config,
	GPIO_Wrong_Pin_Config,
	GPIO_Wrong_Speed_Config,
	GPIO_Wrong_Mode_Config,
	GPIO_WRONG_STATE,
	GPIO_NULL_ptr
}GPIO_Errorstate_t;











/****************************** Gpio_enuInit *******************************************
* @description  :  Initialize the ports of the GPIO peripheral ------------------------*
* @param        :        Add_strPortConfg (GPIOPortConfg_t) : structure	               *
* 	                            GPIOMode :  GPIO_MODE_INPUT_FLOATING                   *
*                                       GPIO_MODE_INPUT_PU                             *
*                                       GPIO_MODE_INPUT_PD                             *
*                                       GPIO_MODE_OUTPUT_PP                            *
*                                       GPIO_MODE_OUTPUT_PP_PU                         *
*                                       GPIO_MODE_OUTPUT_PP_PD                         *
*                                       GPIO_MODE_OUTPUT_OPENDRAIN                     *
*                                       GPIO_MODE_OUTPUT_OPENDRAIN_PU                  *
*                                       GPIO_MODE_OUTPUT_OPENDRAIN_PD                  *
*                                       GPIO_MODE_AF_PP	                               *
*                                       GPIO_MODE_AF_PP_PU                             *
*                                       GPIO_MODE_AF_PP_PD                             *
*                                       GPIO_MODE_AF_OPENDRAIN                         *
*                                       GPIO_MODE_AF_OPENDRAIN_PU                      *
*                                       GPIO_MODE_AF_OPENDRAIN_PD                      *
*                                                                                      *
*                              GPIOSpeed : GPIO_OUTPUT_SPEED_LOW                       *
*                                       GPIO_OUTPUT_SPEED_MEDIUM                       *
*                                       GPIO_OUTPUT_SPEED_HIGH                         *
*                                       GPIO_OUTPUT_SPEED_VERYHIGH                     *
*                                                                                      *
*                               GPIOPort  : GPIO_PORTA, GPIO_PORTB, GPIO_PORTC         *
*                                       GPIO_PORTD, GPIO_PORTE, GPIO_PORTH             *
*                                                                                      *
*                               GPIOPin   : GPIO_PIN0 : GPIO_PIN15                     *
*                                                                                      *
*                   #support to configure many pins in the same port at once           *
* @return      :  error, choosing a wrong pin, port or speed   ------------------------*
****************************************************************************************/
GPIO_Errorstate_t Gpio_enuInit(GPIO_Pinconfig_t* Add_strPortConfg);

/****************************** Gpio_enuSetBit *****************************************
* @description  :  Set the pin in the register by a value (HIGH, LOW) ---------------- *
*                                                                                      *
* @param        :       Copy_u8Port  (u8) : GPIO_PORTA, GPIO_PORTB, GPIO_PORTC         *
*                                           GPIO_PORTD, GPIO_PORTE, GPIO_PORTH         *
*                                                                                      *
*                       Copy_u8Value (u8) : GPIO_VALUE_SET, GPIO_VALUE_RESET           *
*                                                                                      *
*                       Copy_u16Pin  (u8) : GPIO_PIN0 : GPIO_PIN15                     *
*                   #support to configure many pins in the same port at once.          *
* @return       :  error, choosing a wrong pin, port or value   -----------------------*
****************************************************************************************/
GPIO_Errorstate_t GPIO_SetPin_value(void* Copy_Port, u32 pin_num,u32 Copy_Value);

/****************************** Gpio_enuGetBit *****************************************
* @description  :  get the pin in the register by a value (HIGH, LOW) ---------------- *
*                                                                                      *
* @param        :       Copy_u8Port  (u8) : GPIO_PORTA, GPIO_PORTB, GPIO_PORTC         *
*                                           GPIO_PORTD, GPIO_PORTE, GPIO_PORTH         *
*                                                                                      *
*                       Add_p8Value (u8*) : GPIO_VALUE_SET, GPIO_VALUE_RESET           *
*                                       -> to return the value                         *
*                       Copy_u16Pin  (u8) : GPIO_PIN0 : GPIO_PIN15                     *
*                   #support to configure many pins in the same port at once.          *
* @return       :  error, choosing a wrong pin, port or value   -----------------------*
****************************************************************************************/
GPIO_Errorstate_t GPIO_GetPin_value(u8 Copy_Port, u16 Copy_Pin, u32* Copy_Value);





#endif /* GPIO_H_ */

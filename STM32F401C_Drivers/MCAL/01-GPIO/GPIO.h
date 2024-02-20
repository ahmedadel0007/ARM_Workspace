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

#define GPIO_portA  0
#define GPIO_portB  1
#define GPIO_portC  2
#define GPIO_portD  3




#define GPIO_PIN0			((u16)0x0001)
#define GPIO_PIN1			((u16)0x0002)
#define GPIO_PIN2			((u16)0x0004)
#define GPIO_PIN3			((u16)0x0008)
#define GPIO_PIN4			((u16)0x0010)
#define GPIO_PIN5			((u16)0x0020)
#define GPIO_PIN6			((u16)0x0040)
#define GPIO_PIN7			((u16)0x0080)
#define GPIO_PIN8			((u16)0x0100)
#define GPIO_PIN9			((u16)0x0200)
#define GPIO_PIN10			((u16)0x0400)
#define GPIO_PIN11			((u16)0x0800)
#define GPIO_PIN12			((u16)0x1000)
#define GPIO_PIN13			((u16)0x2000)
#define GPIO_PIN14			((u16)0x4000)
#define GPIO_PIN15			((u16)0x8000)


#define GPIO_total_ports   5
#define GPIO_total_pins    15


/* MODE CONFIGURATION */
#define GPIO_MODE_INPUT_FLOATING 0x00000000
#define GPIO_MODE_INPUT_PU       0x00000001
#define GPIO_MODE_INPUT_PD       0x00000002

#define GPIO_MODE_OUTPUT_PP        0x00000008
#define GPIO_MODE_OUTPUT_PP_PU     0x00000009
#define GPIO_MODE_OUTPUT_PP_PD     0x0000000A

#define GPIO_MODE_OUTPUT_OPENDRAIN          0x0000000C
#define GPIO_MODE_OUTPUT_OPENDRAIN_PU       0x0000000D
#define GPIO_MODE_OUTPUT_OPENDRAIN_PD       0x0000000E

#define GPIO_MODE_AF_PP             0x00000010
#define GPIO_MODE_AF_PP_PU          0x00000011
#define GPIO_MODE_AF_PP_PD          0x00000012

#define GPIO_MODE_AF_OPENDRAIN      0x00000014
#define GPIO_MODE_AF_OPENDRAIN_PU   0x00000015
#define GPIO_MODE_AF_OPENDRAIN_PD   0x00000016

#define GPIO_MODE_ANALOG            0x00000018

#define GPIO_PIN_NUM 15

#define GPIO_FALSE 0
#define GPIO_TRUE  1

#define GPIO_VALUE_RESET 0
#define GPIO_VALUE_SET 1


#define GPIO_STATE_HIGH  1
#define GPIO_STATE_LOW   0
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
GPIO_Errorstate_t Gpio_SetPin_value(void* Copy_Port, u32 Copy_Pin, u32 Copy_Value);

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
GPIO_Errorstate_t Gpio_GetPin_value(void* Copy_Port, u16 Copy_Pin, u8* Copy_Value);





#endif /* GPIO_H_ */

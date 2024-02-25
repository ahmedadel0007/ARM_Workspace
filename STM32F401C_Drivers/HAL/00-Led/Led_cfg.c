/*
 * Led_cfg.c
 *
 *  Created on:  20, 2024
 *      Author: Ahmed Adel
 */

#include "GPIO.h"
#include "Led.h"


const Led_cfg_t LEDS [_LED_Num]={
		[led_ALarm]={
				.LED_Port=GPIO_portA,
				.LED_Pin=GPIO_PIN0,
				.LED_Connection=LED_Connection_foward,
				.LED_MODE=GPIO_MODE_AF_PP_PU,
				.LED_Speed=GPIO_SPEED_HIGH,
		},
		[led_RED]=    {
				.LED_Port=GPIO_portA,
				.LED_Pin=GPIO_PIN1,
				.LED_Connection=LED_Connection_foward,
				.LED_MODE=GPIO_MODE_AF_PP_PU,
				.LED_Speed=GPIO_SPEED_LOW,
		}

};

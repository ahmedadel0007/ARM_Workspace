/*
 * SchedApp1.c
 *
 *  Created on: Mar 14, 2024
 *      Author: HP
 */



#include "LED.h"
void Runnable_Toggle_Led1(void)
{
    /* Static variables to keep track of counter and LED status */
  static u32 COUNTER = 0 ;
  static u32 status = LED_STATE_ON ;
  /* Increment the counter */
  COUNTER++;
  /* Check if the counter reaches 1000 milliseconds */
  if ((COUNTER % 300) ==0)
  {
  /* Toggle the LED status */
	status ^= (LED_STATE_ON | LED_STATE_OFF);
  }
    /* Set the LED status */
  Led_SetStatus(led_RED,status);
}

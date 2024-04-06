/*
 * GPIO.c
 *
 *  Created on:  18, 2024
 *      Author: Ahmed Adel
 */
#include"GPIO.h"

typedef struct{
	     u32 MODER;
		 u32 OTYPER;
		 u32 OSPEEDR;
		 u32 PUPDR;
		 u32 IDR;
		 u32 ODR;
		 u32 BSRR;
		 u32 LCKR;
		 u32 AFRL;
		 u32 AFRH;
}GPIO_Reg_t;



volatile GPIO_Reg_t * const GPIO[NUMBER_OF_PORTS] =
{
  GPIO_A, 
  GPIO_B,
  GPIO_C ,
};

#define HALF_WORD  16


#define GET_MODER    0x00000003
#define GET_PUPDR    0x3
#define GET_OTYPER   0x1
//===========================================================//
#define RESET_PUPDR  0x3
#define RESET_MODER  0x00000003
#define RESET_SPEED  0x3
#define RESET_OTYPER 0x1
//===========================================================//


GPIO_Errorstate_t Gpio_enuInit(GPIO_Pinconfig_t* Pin_config){
	u32 local_MODER_HELPER;
	u32 local_PUPDR_HELPER;
	u32 local_OTYPER_HELPER;
	u32 local_OSPEEDR_HELPER;

	GPIO_Errorstate_t local_errorstate =GPIO_Ok;

	if ( (Pin_config ->GPIO_pinnumber < GPIO_PIN0 ) || (Pin_config ->GPIO_pinnumber > GPIO_PIN15 ) )
	{
		local_errorstate=GPIO_Wrong_Pin_Config;
	}

	else if ((Pin_config ->GPIO_SPEED < GPIO_SPEED_LOW)||(Pin_config ->GPIO_SPEED > GPIO_SPEED_VERY_HIGH))
	{
		local_errorstate=GPIO_Wrong_Speed_Config;
	}
	else if ((Pin_config->GPIO_MODE < GPIO_MODE_INPUT_FLOATING)||(Pin_config->GPIO_MODE > GPIO_MODE_AF_OD_PD))
	{
		local_errorstate=GPIO_Wrong_Mode_Config;

	}
	else
	{
		//========================MODER==========================================//
		local_MODER_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->MODER;
		local_MODER_HELPER &=~ (RESET_MODER<<(2*(Pin_config->GPIO_pinnumber)));
		local_MODER_HELPER |=  ((GET_MODER & Pin_config->GPIO_MODE)<<(2*(Pin_config->GPIO_pinnumber)));
		((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->MODER=local_MODER_HELPER;
         Pin_config->GPIO_MODE >>= 2;
		//===============================PUPDR===============================//
		local_PUPDR_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->PUPDR;
		local_PUPDR_HELPER &=~ (RESET_PUPDR<<(2*Pin_config->GPIO_pinnumber));
		local_PUPDR_HELPER |=  ((GET_PUPDR & Pin_config->GPIO_MODE)<<(2*Pin_config->GPIO_pinnumber));
		((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->PUPDR=local_PUPDR_HELPER;
		 Pin_config->GPIO_MODE >>= 2;
		//===============================OTYPER===============================//

		local_OTYPER_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->OTYPER;
		local_OTYPER_HELPER &=~ (RESET_OTYPER<<(Pin_config->GPIO_pinnumber));
		local_OTYPER_HELPER |=  (GET_OTYPER<<(Pin_config->GPIO_pinnumber));
		((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->OTYPER=local_PUPDR_HELPER;

		//===============================OSPEEDR===============================//

		local_OSPEEDR_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->OSPEEDR;
		local_OSPEEDR_HELPER &=~ (RESET_SPEED<<(2*Pin_config->GPIO_pinnumber));
		local_OSPEEDR_HELPER |=  (Pin_config->GPIO_SPEED<<(2*Pin_config->GPIO_pinnumber));
		((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->OSPEEDR=local_OSPEEDR_HELPER;


	}
	return local_errorstate ;
}


//===================================================================================================//

GPIO_Errorstate_t GPIO_SetPin_value(void* Copy_Port, u32 pin_num,u32 Copy_Value){

	GPIO_Errorstate_t local_errorstate =GPIO_Ok;
	if (pin_num >GPIO_PIN15 )
	{
		local_errorstate=GPIO_Wrong_Pin_Config;
	}

	else if ((Copy_Value != GPIO_STATE_HIGH) && (Copy_Value != GPIO_STATE_LOW))
	{
		local_errorstate=GPIO_WRONG_STATE;
	}

	else if (Copy_Port == NULL)
	{
		local_errorstate=GPIO_NULL_ptr;
	}
	else
	{
		switch (Copy_Value)
		{

		case GPIO_STATE_HIGH:
		(((GPIO_Reg_t*)(Copy_Port))->BSRR) |= (1 << pin_num);

			break;
		case GPIO_STATE_LOW:
			((GPIO_Reg_t*)(Copy_Port))->BSRR |= (1 << (pin_num + HALF_WORD));
		    break;
		        default:
		            local_errorstate = GPIO_Nok;
		            break;


		}

	}
	return local_errorstate ;

}

//=====================================================================================================//

GPIO_Errorstate_t GPIO_GetPin_value(u8 Copy_Port, u16 Copy_Pin, u32* Copy_Value){
	

	GPIO_Errorstate_t ReturnError = GPIO_Ok;
	u32 Local_Reg;
		if(Copy_Port > NUMBER_OF_PORTS)
		{
			ReturnError = GPIO_Nok;
		}
		else if(Copy_Pin > GPIO_total_pins)
		{
			ReturnError = GPIO_Nok;
		}
		else if(Copy_Value == NULL)
		{
				ReturnError = GPIO_NULL_ptr;
		}
		else
		{
		    	Local_Reg = GPIO[Copy_Port] -> IDR;
			*Copy_Value = (Local_Reg & (1 << Copy_Pin)) >> Copy_Pin;
		}
		return ReturnError;
}


//======================================================================================================//

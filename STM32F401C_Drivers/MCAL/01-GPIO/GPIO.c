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


#define HALF_WORD  16
#define GPIOA  ((void *)(0x40020000))
#define GPIOB  ((void *)(0x40020400))
#define GPIOC  ((void *)(0x40030800))

#define GET_MODER    0x3
#define GET_PUPDR    0x3
#define GET_OTYPER   0x4
//===========================================================//
#define RESET_PUPDR  0x3
#define RESET_MODER  0x3
#define RESET_SPEED  0x3
#define RESET_OTYPER 0x1
//===========================================================//


GPIO_Errorstate_t Gpio_enuInit(GPIO_Pinconfig_t* Pin_config){
	u32 local_MODER_HELPER;
	u32 local_PUPDR_HELPER;
	u32 local_OTYPER_HELPER;
	u32 local_OSPEEDR_HELPER;

	GPIO_Errorstate_t local_errorstate =GPIO_Ok;

	if ( (Pin_config ->GPIO_pinnumber < GPIO_PIN0  ) || (Pin_config ->GPIO_pinnumber >GPIO_PIN15 ) )
	{
		local_errorstate=GPIO_Wrong_Pin_Config;
	}

	else if (!(Pin_config ->GPIO_SPEED == GPIO_SPEED_LOW)||(Pin_config ->GPIO_SPEED == GPIO_SPEED_VERY_HIGH))
	{
		local_errorstate=GPIO_Wrong_Speed_Config;
	}
	else if ((Pin_config->GPIO_MODE > GPIO_MODE_INPUT_FLOATING)||(Pin_config->GPIO_MODE < GPIO_MODE_ANALOG))
	{
		local_errorstate=GPIO_Wrong_Mode_Config;

	}
	else
	{
		//========================MODER==========================================//
		local_MODER_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->MODER;
		local_MODER_HELPER &=~ (RESET_MODER<<(2*Pin_config->GPIO_pinnumber));
		local_MODER_HELPER |=  (GET_MODER<<(2*Pin_config->GPIO_pinnumber));
		((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->MODER=local_MODER_HELPER;

		//===============================PUPDR===============================//
		local_PUPDR_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->PUPDR;
		local_PUPDR_HELPER &=~ (RESET_PUPDR<<(2*Pin_config->GPIO_pinnumber));
		local_PUPDR_HELPER |=  (GET_PUPDR<<(2*Pin_config->GPIO_pinnumber));
		((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->PUPDR=local_PUPDR_HELPER;
		//===============================OTYPER===============================//

		local_OTYPER_HELPER = ((GPIO_Reg_t*)(Pin_config->GPIO_portnumber))->OTYPER;
		local_OTYPER_HELPER &=~ (RESET_OTYPER<<(2*Pin_config->GPIO_pinnumber));
		local_OTYPER_HELPER |=  (GET_OTYPER<<(2*Pin_config->GPIO_pinnumber));
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

GPIO_Errorstate_t Gpio_SetPin_value(void* Copy_Port, u32 Copy_Pin,u32 Copy_Value){

	GPIO_Errorstate_t local_errorstate =GPIO_Ok;
	if ( ( Copy_Pin < GPIO_PIN0  ) || (Copy_Pin  >GPIO_PIN15 ) )
	{
		local_errorstate=GPIO_Wrong_Pin_Config;
	}

	else if (!(Copy_Value ==GPIO_STATE_HIGH)||(Copy_Value == GPIO_STATE_LOW))
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
			((GPIO_Reg_t*)(Copy_Port))->BSRR |= (1 << Copy_Pin);

			break;
		case GPIO_STATE_LOW:
			((GPIO_Reg_t*)(Copy_Port))->BSRR |= (1 << (Copy_Pin + HALF_WORD));
			break;

		}

	}
	return local_errorstate ;

}

//=====================================================================================================//

GPIO_Errorstate_t Gpio_GetPin_value(void* Copy_Port, u16 Copy_Pin, u8* Copy_Value){
	GPIO_Errorstate_t local_errorstate =GPIO_Ok;

	if ( ( Copy_Pin < GPIO_PIN0  ) || (Copy_Pin  >GPIO_PIN15 ) )
	{
		local_errorstate=GPIO_Wrong_Pin_Config;
	}



	else if ((Copy_Port == NULL) || (Copy_Value == NULL) )
	{
		local_errorstate=GPIO_NULL_ptr;
	}
	else
	{
		*Copy_Value=(((GPIO_Reg_t*)(Copy_Port))->IDR &(1 <<Copy_Pin));

	}
return local_errorstate;
}

//======================================================================================================//

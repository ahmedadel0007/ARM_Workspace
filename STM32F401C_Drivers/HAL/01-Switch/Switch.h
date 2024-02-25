/*
 * Switch.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Ahmed Adel
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include"Switch_cfg.h"
#include"STD_TYPES.h"
//================================Defines=================================//
#define Switch_pressed    1
#define Switch_Notpressed 0

#define Switch_input_PU   1
#define Switch_input_PD    0


//======================================Types================================//

typedef struct{
	void* Switch_port;
	u32 Switch_pin;
	u32 Switch_Mode;


}Switch_cfg_t;


typedef enum{
	Switch_ok,
	Switch_nok,
	Switch_invalid_Switch,
	Switch_Nullptr


}Switch_errorstate_t;



//================================================ Function Prototypes ========================================//

/**
 * @brief: Initializes the SWITCH according to external SWITCH configuration.
 *
 * @return: SWITCH_ERRORSTATUS_t :
 *         - SWITCH_OK
 *         - GPIO_ERRORStatus
 */

Switch_errorstate_t Switch_init(void);

/**
 * @brief: Sets the status of the specified SWITCH.
 *
 * @param: - Copy_SWITCH: The name of the SWITCH whose status will be set.
 *         - Copy_Status: The status of the SWITCH (SWITCH_PRESSED, SWITCH_NOT_PRESSED).
 *
 * @return: SWITCH_ERRORSTATUS_t:
 *         - SWITCH_OK
 *         - SWITCH_InvalidSwitch
 *         - SWITCH_NULLPTR
 *         - GPIO_ERRORStatus
 */


Switch_errorstate_t Switch_Get_state (u32 copy_Switch , u8* copy_state);


#endif /* SWITCH_H_ */

/*
 * Schedular.h
 * Description: Header file for schedular
 *  Created on: Mar 12, 2024
 *      Author: Ahmed Adel
 *================================================================================
 */

#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_
//========================includes===========================================//
#include "RunnableList_Cfg.h"
#include "STD_TYPES.h"
#include "STK.h"

//=============Types========================================================//
typedef void (*Runnable_CBF_t)(void);




typedef struct {
	char*name;
	u32 periodicityMS;
	u32 priority;
	u32 DelayMS;
	Runnable_CBF_t CBF;

}Runnable_t;

typedef enum{
	Sched_ok,
	Sched_NOK,
	Sched_NullPtr
}Sched_ERRORSTATE_t;
//====================================API's==================================//

void Sched_Init  (void);

void Sched_Start (void);





#endif /* SCHEDULAR_H_ */

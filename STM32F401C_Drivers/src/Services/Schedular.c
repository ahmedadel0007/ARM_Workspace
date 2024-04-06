/*
 * Schedular.c
 *Description : Source file for schedular
 *  Created on: Mar 12, 2024
 *      Author: Ahmed Adel
 *==========================================================================
 */

#include "Schedular.h"


//============================Global Variables===============================//
static volatile u32 Pending_ticks ;
extern const Runnable_t RunnableList [_RUN_NUM];

//==============================Defines======================================//
#define tickTime_MS   10

//======================Static Functions =====================================//

static void Sched (void);
static void Tickcbf (void);

//======================Implementation===========================================//

void Sched_Init (void){

	STK_SetConfig(STK_ProcessorClock_EN_INT);
	STK_SetTimeMS (tickTime_MS);
	STK_SetCallBack (Tickcbf);
}

void Sched_Start (void){


	STK_Strat ();
	while (1){
		if (Pending_ticks){
			Pending_ticks -- ;
			Sched ();
		}

	}

}


void Sched (void){

	u32 idx;
	static u32 Timestamp = 0;

	for(idx=0 ; idx < _RUN_NUM; idx ++){

		if((RunnableList[idx].CBF) &&(Timestamp % RunnableList[idx].periodicityMS ==0)){

			RunnableList[idx].CBF();
		}
	}

	Timestamp += tickTime_MS;
}


static void Tickcbf (void)
{
	Pending_ticks ++ ;
}

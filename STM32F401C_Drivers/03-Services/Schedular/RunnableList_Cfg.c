/*
 * RunnableList_Cfg.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Ahmed Adel
 */


#include "Schedular.h"
#include "RunnableList_Cfg.h"

const Runnable_t RunnableList [_RUN_NUM]={
		[app1]={.name ="ToggleLed1",.periodicityMS=10,.CBF=Runnable_Toggle_Led1},
		[app2]={.name ="ToggleLed2",.periodicityMS=20,.CBF=Runnable_Toggle_Led2},
};


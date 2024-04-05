/*
 * RunnableList_Cfg.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Ahmed Adel
 */


#include "Schedular.h"
#include "RunnableList_Cfg.h"
void LCDTest_Runnable(void);

const Runnable_t RunnableList [_RUN_NUM]={
		[app1]={.name ="TimeStamp",.periodicityMS=1000,.CBF=Runnable_timeStamp},
		[app2]={.name ="view",.periodicityMS=100,.CBF=Runnable_views},
		[app3]={.name="LCD",.periodicityMS=2,.CBF=LCD_Runnable},
		[app4]={.name="Switch",.periodicityMS=25,.CBF=SWITCH_Runabble},
		
	
		
};


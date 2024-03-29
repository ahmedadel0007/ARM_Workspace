/*
 * RunnableList_Cfg.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Ahmed Adel
 */


#include "Schedular.h"
#include "RunnableList_Cfg.h"

const Runnable_t RunnableList [_RUN_NUM]={
		[app1]={.name ="LCD",.periodicityMS=1000,.CBF=LCDTest_Runnable},
		[app2]={.name ="LCD_Runnable",.periodicityMS=4,.CBF=LCD_Runnable},
};


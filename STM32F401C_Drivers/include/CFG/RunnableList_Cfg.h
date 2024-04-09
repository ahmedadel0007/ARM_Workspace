/*
 * RunnableList_Cfg.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Ahmed Adel
 */

#ifndef RUNNABLELIST_Cfg_H_
#define RUNNABLELIST_Cfg_H_

 typedef enum
{
    app1 ,
    app2 ,
    app3 ,
    app4 ,
    app5 ,
    app6 ,
	_RUN_NUM,

}Run_t;

extern void LCD_Runnable (void);

extern void LCDTest_Runnable(void) ;

extern void Runnable_views (void);

extern void Runnable_timeStamp (void);

extern void switch_Task(void);

extern void SWITCH_Runabble(void);

//extern void StopWatchMs(void);


#endif /* RUNNABLELIST_CFG_H_ */

#include "Schedular.h"
#include "LCD.h"
#include "RCC_interface.h"


void LCDTest_Runnable(void)
{
  static u32 time=0;
    if (time==3)
    {
    	LCD_WriteString_Asynch("Hello",5);
    }
    else if (time==4)
    {
    	 LCD_ClearScreen_Asynch ();
    }
    else if (time==5)
    {
    	LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2 , LCD_DISPLAY_COL3);
    }
    else if (time==6)
    {
    	LCD_WriteString_Asynch("Ahmed",5);
    }
    time ++ ;
}
int main (void)
{
	RCC_enuEnablePreipheral(AHB1_BUS,GPIOB_RCC);

	LCD_Init_Asynch();
	Sched_Init();
	Sched_Start();
}


#include "NVIC.h"
#include "RCC_interface.h"
#include "Schedular.h"
#include "STK.h"
#include "LCD.h"
#include "Switch.h"

#define VIEW_1 1
#define VIEW_2 2
#define VIEW_3 3
#define VIEW_4 4

u32 current_pressedswitch = _Switch_Num;
u8 Default_View = 0;
u8 Choose_View = 0;
u8 StopWatch_View = 0;

static void Display_Date_time(void);
static void Display_View2(void);
static void Display_View3(void);
void switch_Task(void);
void StopWatchMs(void);

typedef enum
{
    Start,
    Stop,
    Reset,
} SW_Mode_t;

SW_Mode_t StopWatch_State = Reset;

typedef struct
{
    u8 Hours;
    u8 Minutes;
    u8 Seconds;

} Clock_t;

Clock_t Time;

typedef struct
{
    u8 Hours;
    u8 Minutes;
    u8 Seconds;
    u8 MilliSec;
} StopWatch_t;

StopWatch_t SW;

typedef enum
{
    StopWatch,
    EditTime
} Status_t;

Status_t Status;

char StopWatch_time[16];
char Current_time[8];
char Current_date[10];
/********************Runnables**********************************************************/
void Runnable_views(void)
{
    
    static u8 VIEWS = VIEW_1;
    switch (VIEWS)
    {
    case VIEW_1:

        Display_Date_time();

        if (current_pressedswitch == Switch_mode)
        {
            Default_View++;
            LCD_ClearScreen_Asynch();
            VIEWS = VIEW_2;
        }

        break;

    case VIEW_2:

        if (Default_View == 1)
        {
            Display_View2();
        }
        if (Default_View == 2 && current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 0;
            VIEWS = VIEW_1;
        }
        else if (Default_View == 2 && current_pressedswitch == Switch_up)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 0;
            VIEWS = VIEW_3;
        }
        else if (Default_View == 2 && current_pressedswitch == Switch_down)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 0;
            StopWatch_View = 0;
            VIEWS = VIEW_4;
        }

        break;

    case VIEW_3:
 
         Display_View3();
        if (Choose_View == 1)
        {
            StopWatch_State =Reset;
            //Choose_View++;
            Display_View3();
            
        }
        if ( Choose_View >=2 && current_pressedswitch== Switch_up){
                
                 StopWatch_State= Start;
                  Display_View3();
        }

        if (current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 1;
            Choose_View = 0;
            VIEWS = VIEW_2;
        }

        break;

    case VIEW_4:
        break;

    default:
        break;
    }
}

void Runnable_timeStamp(void)
{

    Time.Seconds++;
    if (Time.Seconds > 59)
    {
        Time.Seconds = 0;
        Time.Minutes++;
        if (Time.Minutes > 59)
        {
            Time.Minutes = 0;
            Time.Hours++;
            if (Time.Hours > 23)
            {
                Time.Hours = 0;
                Time.Minutes = 0;
                Time.Seconds = 0;
            }
        }
    }
}

void StopWatchMs(void)
{

    SW.MilliSec++;
    if (SW.MilliSec > 9)
    {
        SW.Seconds++;
        SW.MilliSec = 0;
        if (SW.Seconds > 59)
        {
            SW.Minutes++;
            SW.Seconds = 0;
            SW.MilliSec = 0;
            if (SW.Minutes > 59)
            {
                SW.Hours++;
                SW.Minutes = 0;
                SW.Seconds = 0;
                SW.MilliSec = 0;
            }
        }
    }
}

void Display_Date_time(void)
{

    static u8 counter = 0;
    counter++;

    if (counter == 2)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }
    if (counter == 4)
    {
        LCD_WriteString_Asynch("4/4/2024", 8);
    }
    else if (counter == 6)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }
    else if (counter == 8)
    {

        Current_time[0] = 48 + (Time.Hours / 10);
        Current_time[1] = 48 + (Time.Hours % 10);

        Current_time[2] = 58;

        Current_time[3] = 48 + (Time.Minutes / 10);
        Current_time[4] = 48 + (Time.Minutes % 10);
        Current_time[5] = 58;

        Current_time[6] = 48 + (Time.Seconds / 10);
        Current_time[7] = 48 + (Time.Seconds % 10);
        LCD_WriteString_Asynch(Current_time, 8);
        counter = 0;
    }
}

void Display_View2(void)
{
    static u8 timecounter = 0;
    timecounter++;

    if (timecounter == 3)
    {
        LCD_ClearScreen_Asynch();
    }

    else if (timecounter == 6)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }

    else if (timecounter == 9)
    {
        LCD_WriteString_Asynch("StopWatch", 9);
    }

    else if (timecounter == 12)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }

    else if (timecounter == 15)
    {
        LCD_WriteString_Asynch("Edit Time&Date  ", 16);
        timecounter = 0;
        Default_View++;
    }
}

void switch_Task(void)
{
    u8 counter;
    u8 Switch_state;
    current_pressedswitch = 8;
    for (counter = 0; counter < _Switch_Num; counter++)
    {

        Switch_GetSwitchState(counter, &Switch_state);
        if (Switch_state == SWITCH_PRESSED)
        {

            current_pressedswitch = counter;
            counter = _Switch_Num;
        }
    }
}

void Display_View3(void)
{
    static u8 counter = 0;
    //static u8 startcounter = 0;
    
    counter++;
      if (counter == 4)
        {
             LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
       }
       else if (counter == 8)
        {
            LCD_WriteString_Asynch("STOPWATCH", 9);
        }
        else if (counter == 12)
        {
            LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
        }
         if (counter==16 && StopWatch_State ==Reset)
        {
           
            StopWatch_time[0] = 48;
            StopWatch_time[1] = 48;

            StopWatch_time[2] = 58;

            StopWatch_time[3] = 48;
            StopWatch_time[4] = 48;

            StopWatch_time[5] = 58;

            StopWatch_time[6] = 48;
            StopWatch_time[7] = 48;

            StopWatch_time[8] = 32;     //58;

            StopWatch_time[9] = 32;
            StopWatch_time[10]= 32;
            StopWatch_time[11]= 32;
            StopWatch_time[12]= 32;
            StopWatch_time[13]= 32;
            StopWatch_time[14]= 32;
            StopWatch_time[15]= 32;


            LCD_WriteString_Asynch(StopWatch_time,16);
            counter = 0;
            Choose_View++;
          
           // StopWatch_State =Start;
           
        }
    
    else if (counter ==16 && StopWatch_State == Start)
       {
            
            StopWatch_time[0] = 48 + (SW.Hours / 10);
            StopWatch_time[1] = 48 + (SW.Hours % 10);

            StopWatch_time[2] = 58;

            StopWatch_time[3] = 48 + (SW.Minutes / 10);
            StopWatch_time[4] = 48 + (SW.Minutes % 10);

            StopWatch_time[5] = 58;

            StopWatch_time[6] = 48 + (SW.Seconds / 10);
            StopWatch_time[7] = 48 + (SW.Seconds % 10);

            //StopWatch_time[8] = 58;

            StopWatch_time[9] = 32;    //48 + (SW.MilliSec % 7000);
            StopWatch_time[10]= 32;//48 + (SW.MilliSec % 1000);
            StopWatch_time[11]= 32;
            StopWatch_time[12]= 32;
            StopWatch_time[13]= 32;
            StopWatch_time[14]= 32;
            StopWatch_time[15]= 32;

            LCD_WriteString_Asynch(StopWatch_time,16);
            counter = 0;
            Choose_View++;
        }
}

int main(int argc, char *argv[])
{
    // Enable GPIOB peripheral clock
    RCC_enuEnablePreipheral(AHB1_BUS, GPIOB_RCC);
    RCC_enuEnablePreipheral(AHB1_BUS, GPIOA_RCC);

    // Initialize LCD asynchronously
    LCD_Init_Asynch();

    Switch_Init();
    // Initialize Scheduler
    Sched_Init();

    // Start Scheduler
    Sched_Start();

    // This point will not be reached as the scheduler will start running
}

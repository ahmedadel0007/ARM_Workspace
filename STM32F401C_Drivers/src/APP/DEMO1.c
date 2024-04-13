#include "NVIC.h"
#include "RCC_interface.h"
#include "Schedular.h"
#include "STK.h"
#include "LCD.h"
#include "Switch.h"

#define VIEW_1 1
#define VIEW_2 2
#define VIEW_3 3
#define VIEW_3_1 4
#define VIEW_3_2 5
#define VIEW_3_3 6
#define VIEW_4 7
#define UP 1
#define DOWN 2

u32 current_pressedswitch = _Switch_Num;
u8 Default_View = 0;
u8 Choose_View = 0;
u8 StopWatch_View = 0;
u8 Edit_View = 0;
u8 EditMode;
u8 CursorPosition = 0;

static void Display_Date_time(void);
static void Display_View2(void);
static void Display_View3(void);
static void Display_View3_1(void);
static void Display_View3_2(void);
static void Display_View3_3(void);
void switch_Task(void);
void StopWatchMs(void);
static void Display_Edit_Time(void);
void Edit_Date_Time(void);

typedef enum
{
    DEFAULT,
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

typedef struct
{
    u8 Digit_0;
    u8 Digit_1;
    u8 Digit_2;
    u8 Digit_3;
} Digits_t;

typedef struct
{
    Digits_t Year;
    Digits_t Month;
    Digits_t Day;
} Date_t;

Date_t Date;

typedef struct
{
    Digits_t hours;
    Digits_t minutes;
    Digits_t sec;
} Time_t;

Time_t time;

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
        /***************************************************************************************************/
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
            Choose_View++;
            VIEWS = VIEW_3;
        }
        else if (Default_View == 2 && current_pressedswitch == Switch_down)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 0;
            Choose_View++;
            StopWatch_View = 0;
            VIEWS = VIEW_4;
        }

        break;
        /**********************************************************************************************************/
    case VIEW_3: // Default Stopwatch View

        if (Choose_View == 1)
        {
            Display_View3();
        }
        if ( current_pressedswitch == Switch_up)
        {
            VIEWS = VIEW_3_1;
            
        }

        if ( current_pressedswitch == Switch_down)
        {

            VIEWS = VIEW_3_2;
           
        }

        if (current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 1;
            Choose_View = 0;
            VIEWS = VIEW_2;
        }

        break;
    case VIEW_3_1: // Start Stowatch view
       
        Display_View3_1();
        StopWatchMs();
      
        if (current_pressedswitch == Switch_down)
        {
           
            VIEWS = VIEW_3_2;
        }
        if (current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 1;
            VIEWS = VIEW_2;
        }
        break;

    case VIEW_3_2: // stop stopwatch

        // Choose_View = 0;
        Display_View3_2();
        if (current_pressedswitch == Switch_up)
        {
            // Choose_View++;
           
            VIEWS = VIEW_3_1;
        }
        if ( current_pressedswitch == Switch_down)
        {
            VIEWS = VIEW_3_3;
           // Choose_View = 0;
        }
        if (current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 1;
            VIEWS = VIEW_2;
        }
        break;
    case VIEW_3_3: // Reset Stopwatch
        //Choose_View = 0;
        Display_View3_3();
        if (current_pressedswitch == Switch_up)
        {
            VIEWS = VIEW_3;
        }
        if (current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 1;
            //Choose_View = 0;
            VIEWS = VIEW_2;
        }
        break;
        /***************************************************************************************************************/
    case VIEW_4:
        //if (Edit_View == 1)
        //{
            Display_Edit_Time();
            Edit_Date_Time();
        //}
        if (current_pressedswitch == Switch_up)
        {
            EditMode = UP;
        }
        else if (current_pressedswitch == Switch_down)
        {
            EditMode = DOWN;
        }
        else if (current_pressedswitch == Switch_left)
        {
            if (CursorPosition == 0)
            {
                CursorPosition = 13;
            }
            else
            {
                CursorPosition--;
            }
        }
        else if (current_pressedswitch == Switch_right)
        {
            if (CursorPosition == 13)
            {
                CursorPosition = 0;
            }
            else
            {
                CursorPosition++;
            }
        }
        else if (current_pressedswitch == Switch_mode)
        {
            LCD_ClearScreen_Asynch();
            Default_View = 1;
            Choose_View = 0;
            VIEWS = VIEW_2;
        }
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

    if (counter == 3)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }
    if (counter == 6)
    {
        Current_date[0] = 48 + (Date.Day.Digit_0);
        Current_date[1] = 48 + (Date.Day.Digit_1);

        Current_date[2] = 58;

        Current_date[3] = 48 + (Date.Month.Digit_0);
        Current_date[4] = 48 + (Date.Month.Digit_1);

        Current_date[5] = 58;

        Current_date[6] = 48 + (Date.Year.Digit_0);
        Current_date[7] = 48 + (Date.Year.Digit_1);
        Current_date[8] = 48 + (Date.Year.Digit_2);
        Current_date[9] = 48 + (Date.Year.Digit_3);

        LCD_WriteString_Asynch(Current_date, 10);
    }
    else if (counter == 9)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }
    else if (counter == 12)
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

void Display_View3(void) // default stopwatch
{
    static u8 counter = 0;
    counter++;
    if (counter == 4)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }
    else if (counter == 8)
    {
        LCD_WriteString_Asynch("STOPWATCH       ", 16);
    }
    else if (counter == 12)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }
    if (counter == 14)
    {
         StopWatch_time[0] = 48;
        StopWatch_time[1] = 48 ;

        StopWatch_time[2] = 58;

        StopWatch_time[3] = 48 ;
        StopWatch_time[4] = 48 ;

        StopWatch_time[5] = 58;

        StopWatch_time[6] = 48;
        StopWatch_time[7] = 48;

        StopWatch_time[8] = 32; // 58;

        StopWatch_time[9] = 32;  // 48 + (SW.MilliSec % 7000);
        StopWatch_time[10] = 32; // 48 + (SW.MilliSec % 1000);
        StopWatch_time[11] = 32;
        StopWatch_time[12] = 32;
        StopWatch_time[13] = 32;
        StopWatch_time[14] = 32;
        StopWatch_time[15] = 32;
        LCD_WriteString_Asynch(StopWatch_time,16);
        counter = 0;
        Choose_View++;
    }
}

void Display_View3_1(void) // strat stopwatch
{
   // StopWatchMs();
    static u8 counter = 0;
    counter++;
    if (counter == 4)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }
    else if (counter == 8)
    {
        LCD_WriteString_Asynch("STOPWATCH       ", 16);
    }
    else if (counter == 12)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }
    else if (counter == 14)
    {
        StopWatch_time[0] = 48 + (SW.Hours / 10);
        StopWatch_time[1] = 48 + (SW.Hours % 10);

        StopWatch_time[2] = 58;

        StopWatch_time[3] = 48 + (SW.Minutes / 10);
        StopWatch_time[4] = 48 + (SW.Minutes % 10);

        StopWatch_time[5] = 58;

        StopWatch_time[6] = 48 + (SW.Seconds / 10);
        StopWatch_time[7] = 48 + (SW.Seconds % 10);

        StopWatch_time[8] = 32; // 58;

        StopWatch_time[9] = 32;  // 48 + (SW.MilliSec % 7000);
        StopWatch_time[10] = 32; // 48 + (SW.MilliSec % 1000);
        StopWatch_time[11] = 32;
        StopWatch_time[12] = 32;
        StopWatch_time[13] = 32;
        StopWatch_time[14] = 32;
        StopWatch_time[15] = 32;
        LCD_WriteString_Asynch(StopWatch_time, 16);
        counter = 0;
        Choose_View++;
    }
}

void Display_View3_2(void)
{ // stop stopwatch

    static u8 counter = 0;
   
    counter++;
    if (counter == 4)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }
    else if (counter == 8)
    {
        LCD_WriteString_Asynch("STOPWATCH       ", 16);
    }
    else if (counter == 12)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }
    else if (counter == 16)
    {
        StopWatch_time[0] = 48 + (SW.Hours / 10);
        StopWatch_time[1] = 48 + (SW.Hours % 10);

        StopWatch_time[2] = 58;

        StopWatch_time[3] = 48 + (SW.Minutes / 10);
        StopWatch_time[4] = 48 + (SW.Minutes % 10);

        StopWatch_time[5] = 58;

        StopWatch_time[6] = 48 + (SW.Seconds / 10);
        StopWatch_time[7] = 48 + (SW.Seconds % 10);

        StopWatch_time[8] = 32; // 58;

        StopWatch_time[9] = 32;  // 48 + (SW.MilliSec % 7000);
        StopWatch_time[10] = 32; // 48 + (SW.MilliSec % 1000);
        StopWatch_time[11] = 32;
        StopWatch_time[12] = 32;
        StopWatch_time[13] = 32;
        StopWatch_time[14] = 32;
        StopWatch_time[15] = 32;

        LCD_WriteString_Asynch(StopWatch_time, 16);
        Choose_View++;
    }
}

void Display_View3_3(void)
{ // Reset Stopwatch
     SW.Hours=0;
     SW.Minutes=0;
     SW.Seconds=0;
     StopWatch_time[16]= 0;
    static u8 counter = 0;
    counter++;
    if (counter == 4)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1, LCD_DISPLAY_COL1);
    }
    else if (counter == 8)
    {
        LCD_WriteString_Asynch("STOPWATCH       ", 16);
    }
    else if (counter == 12)
    {
        LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2, LCD_DISPLAY_COL1);
    }
    if (counter == 16)
    {
        StopWatch_time[0] =48;
        StopWatch_time[1] = 48 ;

        StopWatch_time[2] = 58;

        StopWatch_time[3] = 48 ;
        StopWatch_time[4] = 48 ;

        StopWatch_time[5] = 58;

        StopWatch_time[6] = 48;
        StopWatch_time[7] = 48;

        StopWatch_time[8] = 32; // 58;

        StopWatch_time[9] = 32;  // 48 + (SW.MilliSec % 7000);
        StopWatch_time[10] = 32; // 48 + (SW.MilliSec % 1000);
        StopWatch_time[11] = 32;
        StopWatch_time[12] = 32;
        StopWatch_time[13] = 32;
        StopWatch_time[14] = 32;
        StopWatch_time[15] = 32;
        LCD_WriteString_Asynch(StopWatch_time,16);
        
        counter = 0;
        Choose_View++;
    }
}

void Edit_Date_Time(void)
{
    if(EditMode == UP)
    {
        switch(CursorPosition)
        {
            case 0:
            if(Date.Day.Digit_1 == 3)
            {
                Date.Day.Digit_1 = 0;
            }
            else
            {
                Date.Day.Digit_1++;
            }
                break;
              
            case 1:
            if(Date.Day.Digit_0 == 9)
            {
                Date.Day.Digit_0 = 0;
            }
            else
            {
                Date.Day.Digit_0++;
            }
                
                break;
            case 2:
            if(Date.Month.Digit_1 == 1)
            {
                Date.Month.Digit_1 = 0;
            }
            else
            {
                Date.Month.Digit_1++;
            }
              
                break;   
            case 3:
            if(Date.Month.Digit_0 == 9)
            {
                Date.Month.Digit_0 = 0;
            }
            else
            {
                Date.Month.Digit_0++;
            }
               
                break;   
            case 4:
            if(Date.Year.Digit_3 == 9)
            {
                Date.Year.Digit_3 = 0;
            }
            else
            {
                Date.Year.Digit_3++;
            }  
                break; 
            case 5:
            if(Date.Year.Digit_2 == 9)
            {
                Date.Year.Digit_2 = 0;
            }
            else
            {
                Date.Year.Digit_2++;
            }
                
                break; 
            case 6:
            if(Date.Year.Digit_1 == 9)
            {
                Date.Year.Digit_1 = 0;
            }
            else
            {
                Date.Year.Digit_1++;
            }
                
                break; 
            case 7:
            if(Date.Year.Digit_0 == 9)
            {
                Date.Year.Digit_0 = 0;
            }
            else
            {
                Date.Year.Digit_0++;
            }
                
                break;
            case 8:
            if(time.hours.Digit_1 == 2)
            {
                time.hours.Digit_1 = 0;
            }                      
            else
            {
                time.hours.Digit_1++;
            }
            Time.Hours=time.hours.Digit_0+(time.hours.Digit_1)*10;
                break;
            case 9:
            if(time.hours.Digit_0 == 9)
            {
                time.hours.Digit_0 = 0;
            }                      
            else
            {
                time.hours.Digit_0++;
            }
            Time.Hours=time.hours.Digit_0+(time.hours.Digit_1)*10;

                break;    
            case 10:
            if(time.minutes.Digit_1 == 5)
            {
                time.minutes.Digit_1 = 0;
            }                      
            else
            {
                time.minutes.Digit_1++;
            }
            Time.Minutes = time.minutes.Digit_0 + (time.minutes.Digit_1)*10;
                break;    
            case 11:
            if(time.minutes.Digit_0 == 9)
            {
                time.minutes.Digit_0 = 0;
            }                      
            else
            {
                time.minutes.Digit_0++;
            }
            Time.Minutes = time.minutes.Digit_0 + (time.minutes.Digit_1)*10;
                break;
            case 12:
            if(time.sec.Digit_1 == 5)
            {
                time.sec.Digit_1 = 0;
            }                      
            else
            {
                time.sec.Digit_1++;
            }
            Time.Seconds = time.sec.Digit_0 + (time.sec.Digit_1)*10;
                break;    
            case 13:
            if(time.sec.Digit_0 == 9)
            {
                time.sec.Digit_0 = 0;
            }                      
            else
            {
                time.sec.Digit_0++;
            }
            Time.Seconds = time.sec.Digit_0 + (time.sec.Digit_1)*10;
                break;
            default:
                break;        

        }
        EditMode = 0;

    }
    else if (EditMode == DOWN)
    {
        switch(CursorPosition)
        {
            case 0:
            if(Date.Day.Digit_1 == 0)
            {
                Date.Day.Digit_1 = 3;
            }
            else
            {
                Date.Day.Digit_1--;
            }
                break;
            case 1:
            if(Date.Day.Digit_0 == 0)
            {
                Date.Day.Digit_0 = 9;
            }
            else
            {
                Date.Day.Digit_0--;
            }    
                break;
            case 2:
            if(Date.Month.Digit_1 == 0)
            {
                Date.Month.Digit_1 = 1;
            }
            else
            {
                Date.Month.Digit_1--;
            }    
                break;   
            case 3:
            if(Date.Month.Digit_0 == 0)
            {
                Date.Month.Digit_0 = 9;
            }
            else
            {
                Date.Month.Digit_0--;
            }    
                break;   
            case 4:
            if(Date.Year.Digit_3 == 0)
            {
                Date.Year.Digit_3 = 9;
            }
            else
            {
                Date.Year.Digit_3--;
            }    
                break; 
            case 5:
            if(Date.Year.Digit_2 == 0)
            {
                Date.Year.Digit_2 = 9;
            }
            else
            {
                Date.Year.Digit_2--;
            }    
                break; 
            case 6:
            if(Date.Year.Digit_1 == 0)
            {
                Date.Year.Digit_1 = 9;
            }
            else
            {
                Date.Year.Digit_1--;
            }    
                break; 
            case 7:
            if(Date.Year.Digit_0 == 0)
            {
                Date.Year.Digit_0 = 9;
            }
            else
            {
                Date.Year.Digit_0--;
            }    
                break;
            case 8:
            if(time.hours.Digit_1 == 0)
            {
                time.hours.Digit_1 = 3;
            }                      
            else
            {
                time.hours.Digit_1--;
            }
                break;
            case 9:
            if(time.hours.Digit_0 == 0)
            {
                time.hours.Digit_0 = 9;
            }                      
            else
            {
                time.hours.Digit_0--;
            }
                break;    
            case 10:
            if(time.minutes.Digit_1 == 0)
            {
                time.minutes.Digit_1 = 5;
            }                      
            else
            {
                time.minutes.Digit_1--;
            }
                break;    
            case 11:
            if(time.minutes.Digit_0 == 0)
            {
                time.minutes.Digit_0 = 9;
            }                      
            else
            {
                time.minutes.Digit_0--;
            }
                break;
            case 12:
            if(time.sec.Digit_1 == 0)
            {
                time.sec.Digit_1 = 5;
            }                      
            else
            {
                time.sec.Digit_1--;
            }
                break;    
            case 13:
            if(time.sec.Digit_0 == 0)
            {
                time.sec.Digit_0 = 9;
            }                      
            else
            {
                time.sec.Digit_0--;
            }
                break;
            default:
                break;        

        }
        EditMode = 0;

    }


}

void Display_Edit_Time(void)
{
    static u8 editcounter=0 ;
    editcounter ++;
    

 if (editcounter == 3){
    LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1,LCD_DISPLAY_COL1);
}

else if (editcounter ==6){
    Current_date[0] = 48 + (Date.Day.Digit_1);
    Current_date[1] = 48 + (Date.Day.Digit_0);

    Current_date[2] = 58 ;

    Current_date[3] = 48 + (Date.Month.Digit_1);
    Current_date[4] = 48 + (Date.Month.Digit_0);

    Current_date[5] = 58 ;

    Current_date[6] = 48 + (Date.Year.Digit_3);
    Current_date[7] = 48 + (Date.Year.Digit_2);
    Current_date[8] = 48 + (Date.Year.Digit_1);
    Current_date[9] = 48 + (Date.Year.Digit_0);

    LCD_WriteString_Asynch (Current_date,10);
}

else if (editcounter ==9){
    LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2,LCD_DISPLAY_COL1);
}

else if (editcounter == 12){
    Current_time   [0] = 48 + (Time.Hours/10);
    Current_time   [1] =  48 + (Time.Hours%10);

    Current_time  [2] = 58 ;

    Current_time  [3] = 48 + (Time.Minutes/10);
    Current_time  [4]= 48 + (Time.Minutes%10);
    Current_time  [5] = 58 ;

    Current_time  [6] = 48 + (Time.Seconds/10) ;
    Current_time  [7] = 48 + (Time.Seconds%10) ;
    LCD_WriteString_Asynch (Current_time,8);
    editcounter = 0;
     //Edit_View++;

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
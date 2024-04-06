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

u32 current_pressedswitch =_Switch_Num;



static void Display_Date_time(void);
static void Display_View2 (void);
void switch_Task(void);



typedef struct
{
    u8 Hours;
    u8 Minutes;
    u8 Seconds;
} Clock_t;

Clock_t Time;

typedef enum
{
    StopWatch,
    EditTime
}Status_t;

Status_t Status;



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
            VIEWS=VIEW_2;
            LCD_ClearScreen_Asynch();  
        }

        break;

    case VIEW_2:
           
             Display_View2(); 
            //  if (current_pressedswitch == Switch_up){
            //     Status= StopWatch;
            //     VIEWS=VIEW_3;
            //  }   
            //  else if (current_pressedswitch == Switch_down){
            //     VIEWS=VIEW_4;
            //     Status=EditTime;
            //  }
            
              if (current_pressedswitch == Switch_mode){
                    LCD_ClearScreen_Asynch();
                     VIEWS= VIEW_1;
                     
                   }
                    
                
             
           
        break;

    case VIEW_3:
             

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
        Time.Seconds=0;
        Time.Minutes++;
        if (Time.Minutes > 59)
        {
            Time.Minutes=0;
            Time.Hours++;
            if (Time.Hours >23)
            {
                Time.Hours = 0;
                Time.Minutes = 0;
                Time.Seconds = 0;
            }
        }
    }
}

/***********************Implementation************************************************/
void Display_Date_time(void)
 {
    
    static u8 counter = 0;
    counter++;
   
    if (counter ==2){
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
     else if (counter == 8){

    Current_time  [0] = 48 + (Time.Hours/10);
    Current_time   [1] =  48 + (Time.Hours%10);

    Current_time  [2] = 58 ;

    Current_time  [3] = 48 + (Time.Minutes/10);
    Current_time  [4]= 48 + (Time.Minutes%10);
    Current_time  [5] = 58 ;

    Current_time  [6] = 48 + (Time.Seconds/10) ;
    Current_time  [7] = 48 + (Time.Seconds%10) ;
    LCD_WriteString_Asynch (Current_time,8);
    counter = 0;

}
}

void Display_View2 (void){
static u8 timecounter=0 ;
    timecounter ++;

if(timecounter ==3){
    LCD_ClearScreen_Asynch();
}

else if (timecounter == 6){
    LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE1,LCD_DISPLAY_COL1);
}

else if (timecounter ==9){
    LCD_WriteString_Asynch ("StopWatch",9);
}

else if (timecounter ==12){
    LCD_SetCursorPostion_Asynch(LCD_DISPLAY_LINE2,LCD_DISPLAY_COL1);
}

else if (timecounter == 15){
    LCD_WriteString_Asynch ("Edit Time&Date  ",16);
    timecounter = 0;
}


}

void switch_Task(void)
{
    u8 counter;
    u8 Switch_state;
    current_pressedswitch=8;
    for(counter=0;counter<_Switch_Num;counter++){

        Switch_GetSwitchState(counter,&Switch_state);
        if (Switch_state == SWITCH_PRESSED){

             current_pressedswitch = counter;
             counter = _Switch_Num ;
        }

    }
}

int main(int argc, char *argv[])
{
    // Enable GPIOB peripheral clock
    RCC_enuEnablePreipheral(AHB1_BUS, GPIOB_RCC);
    RCC_enuEnablePreipheral(AHB1_BUS,GPIOA_RCC);

  
    // Initialize LCD asynchronously
    LCD_Init_Asynch();

     Switch_Init();
    // Initialize Scheduler
    Sched_Init();

    // Start Scheduler
    Sched_Start();

    // This point will not be reached as the scheduler will start running
}

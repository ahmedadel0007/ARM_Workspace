/************************************************************************************************************************************************/
/* File             :       LCDc                                                                                                        */
/* AUTHOR           :       Ahmed Adel                                                                                                       */
/* Origin Date      :       3/26/2024                                                                                                            */
/* SWC              :       Character LCD                                                                                                       */
/************************************************************************************************************************************************/



#include "LCD.h"
#include "GPIO.h"

/********************************Defintions***********************************************************************/

#define Enable_ON  0x00000001
#define Enable_OFF 0x00000000
#define control_pins_Num 0x00000003


/**********Commands Options************************/
#define LCD_ZERO_COMMAND 0x00
#define FOUR_BITS_DATA_MODE 0x02
#define LCD_CLEAR_COMMAND 0x01
#define LCD_GO_TO_HOME 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE 0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE 0x28
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_SET_CURSOR_LOCATION 0x80
#define LCD_INCREMENT_CRUSOR_SHIFT_RIGHT_MODE 0x06
/********************Location in DDRAM handler for Lines*********************/
#define INDEX_FOR_LINE_1 0X0
#define INDEX_FOR_LINE_2 0X40
#define INDEX_FOR_LINE_3 0X10
#define INDEX_FOR_LINE_4 0X50
#define WRITE_ON_DDRAM_INDEX 0X80

/***************************************Types enums**************************************************************/
typedef enum {
	LCD_REQ_ready,
	LCD_REQ_busy
}LCD_UserREQ_State;

typedef enum {
	LCD_WriteString,
	LCD_ClearScreen,
	LCD_SetCursiorPostion,
	LCD_NoRequest,

}LCD_UserREQ_Type_t;

typedef enum {
	LCD_Init,
	LCD_Operation,
	LCD_OFF,
}LCD_State_t;

typedef enum {
	LCD_WriteStart,
	LCD_WriteChar,
	LCD_WriteDone,

}LCD_WriteState_t;


typedef enum {
	LCD_PosStrat,
	LCD_Pos,
	LCD_PosEnd

}LCD_SetCursiorPostion_t;

typedef enum {
	LCD_PowerOn=0,
	LCD_FunctionSet=1,
	LCD_DisplayControl=2,
	LCD_ClearDisplay=3,
	LCD_EntryMode=4,
	LCD_EndInit=5,

}LCD_InitMode_t;

typedef struct
{
	u8 Current_Line_Postion;
	u8 Currrent_Col_Postion;

} LCD_Write_t;

typedef struct{

	const u8* String;
	u16 length ;
	LCD_InitMode_t  Init;
	LCD_UserREQ_State State;
	LCD_UserREQ_Type_t Type;
	LCD_Write_t Current_Postion;
}LCD_UserREQ;

/***********************************************************Variables***************************************************/
extern const LCD_CFG_t LCDs [_LCD_PIN_NUMNER];
static u32 LCD_PinEnable = Enable_OFF;
static LCD_State_t LCD_State = LCD_OFF;
static LCD_InitMode_t LCD_Initmode =LCD_PowerOn;
static LCD_WriteState_t WriteState =LCD_WriteStart;
static LCD_Write_t Current_CursiorPostion ;
static LCD_UserREQ UserREQ ;
static LCD_SetCursiorPostion_t SetCursiorPos =LCD_PosStrat;

/*****************************************************Static Functions API's*********************************************/
static LCD_ERRORSTATE_t LCD_InitState (void);
static LCD_ERRORSTATE_t LCD_WriteProc (void);
static LCD_ERRORSTATE_t LCD_PowerON_Proc (void);
static LCD_ERRORSTATE_t SetPosition_Proc (void);
static LCD_ERRORSTATE_t LCD_WriteCommand (u8 command);
static LCD_ERRORSTATE_t LCD_WriteData (u8 data);
static LCD_ERRORSTATE_t LCD_EnableControl (u32 Enable);
static LCD_ERRORSTATE_t LCD_disableControl (u32 Enable);
static LCD_ERRORSTATE_t LCD_ClearScreen_proc (void);
static LCD_ERRORSTATE_t LCD_SetPostion_help(u8 *ptr_to_DDRAM);

/**********************************************************Implementation*************************************************/

void LCD_Runnable (void){


	switch(LCD_State){
	case LCD_Init:
		LCD_InitState();
		break;
	case LCD_Operation:
		if (UserREQ.State==LCD_REQ_busy){

			switch (UserREQ.Type){
			case LCD_WriteString:
				LCD_WriteProc();
				break;
			case LCD_ClearScreen:
				LCD_ClearScreen_proc();
				break;
			case LCD_SetCursiorPostion:
				SetPosition_Proc();
				break;
			default:
				break;
			}
		}
		break;
	case LCD_OFF:
		break;
	default:
		break;
	}

}
/********************************************************************************************/

static LCD_ERRORSTATE_t LCD_InitState (void){
	LCD_ERRORSTATE_t localreturn =LCD_OK;

	switch(LCD_Initmode){
	case LCD_PowerOn:
		localreturn=LCD_PowerON_Proc();
		LCD_Initmode=LCD_FunctionSet;
		break;
	case LCD_FunctionSet:
		localreturn = LCD_WriteCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
		if (LCD_PinEnable == Enable_OFF)
		{
			LCD_Initmode = LCD_DisplayControl;
		}
		break;
	case LCD_DisplayControl:
		localreturn =LCD_WriteCommand(LCD_CURSOR_ON);
		if(LCD_PinEnable == Enable_OFF){
			LCD_Initmode=LCD_ClearDisplay;
		}
		break;
	case LCD_ClearDisplay:
		localreturn =LCD_WriteCommand(LCD_CLEAR_COMMAND);
		if(LCD_PinEnable == Enable_OFF){
			LCD_Initmode=LCD_EntryMode;
		}
		break;
	case LCD_EntryMode:
		localreturn =LCD_WriteCommand(LCD_INCREMENT_CRUSOR_SHIFT_RIGHT_MODE);
		if(LCD_PinEnable == Enable_OFF){
			LCD_Initmode=LCD_EndInit;
		}
		break;
	case LCD_EndInit:
		UserREQ.State =LCD_REQ_ready;
		LCD_State= LCD_Operation;
		break;
	default:
		localreturn=LCD_NOK;
		break;

	}
	return localreturn;
}
/**********************************************************************************************/

static LCD_ERRORSTATE_t LCD_WriteProc (void){
	LCD_ERRORSTATE_t localreturn = LCD_OK;
	switch (WriteState){
	case LCD_WriteStart:
		WriteState=LCD_WriteChar;
		Current_CursiorPostion.Currrent_Col_Postion=0;
		break;
	case LCD_WriteChar:
		if (Current_CursiorPostion.Currrent_Col_Postion != UserREQ.length){
			LCD_WriteData(UserREQ.String[Current_CursiorPostion.Currrent_Col_Postion]);
			if (LCD_PinEnable == Enable_OFF){
				Current_CursiorPostion.Currrent_Col_Postion ++;
			}
		}
		else{
			WriteState=LCD_WriteDone;
		}
		break;
	case LCD_WriteDone:
		LCD_State=LCD_REQ_ready;
		UserREQ.Type=LCD_NoRequest;
		WriteState=LCD_WriteStart;
		break;
	default:
		break;
	}
	return localreturn;
}
/*************************************************************************************************************/

static LCD_ERRORSTATE_t SetPosition_Proc (void){
	LCD_ERRORSTATE_t localreturn = LCD_OK;
	static u8 location=0;
	switch (SetCursiorPos){
	case LCD_PosStrat:
		LCD_SetPostion_help(&location);
		SetCursiorPos=LCD_Pos;
		break;
	case LCD_Pos:
		localreturn= LCD_WriteCommand((WRITE_ON_DDRAM_INDEX+location));
		if (LCD_PinEnable ==Enable_OFF){
			SetCursiorPos=LCD_PosEnd;
		}
		break;
	case LCD_PosEnd:
		UserREQ.State=LCD_REQ_ready;
		UserREQ.Type=LCD_NoRequest;
		SetCursiorPos=LCD_PosStrat;
		break;
	default:
		break;
	}
	return localreturn;
}

/*******************************************ASYNCH FUNCTIONS********************************************************************/

LCD_ERRORSTATE_t LCD_Init_Asynch (void){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	LCD_State=LCD_Init;

	return localreturn;
}

LCD_ERRORSTATE_t LCD_ClearScreen_Asynch (void){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	if ((LCD_State==LCD_Operation)&&(UserREQ.State==LCD_REQ_ready)){
		UserREQ.State=LCD_REQ_busy;
		UserREQ.Type=LCD_ClearScreen;

	}
	else{
		localreturn=LCD_NOK;
	}
	return localreturn;
}


LCD_ERRORSTATE_t LCD_WriteString_Asynch (const u8* string,u8 Length){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	if (string ==NULL){
		localreturn =LCD_NULLPTR;
	}
	else{
		if ((LCD_State==LCD_Operation)&&(UserREQ.State==LCD_REQ_ready)){
			UserREQ.State=LCD_REQ_busy;
			UserREQ.String=string;
			UserREQ.length=Length;
			UserREQ.Type=LCD_WriteString;
		}
		else {
			localreturn =LCD_NOK;
		}

	}
	return localreturn;
}

LCD_ERRORSTATE_t LCD_SetCursorPostion_Asynch (u8 PostionX ,u8 PostionY){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	if ((LCD_State==LCD_Operation)&&(UserREQ.State==LCD_REQ_ready)){
		UserREQ.State=LCD_REQ_busy;
		UserREQ.Type=LCD_SetCursiorPostion;

		Current_CursiorPostion.Current_Line_Postion=PostionX;
		Current_CursiorPostion.Currrent_Col_Postion=PostionY;
	}
	else{
		localreturn=LCD_NOK;

	}
	return localreturn;

}

LCD_ERRORSTATE_t LCD_getState (u8 * LCDstatus){
	LCD_ERRORSTATE_t localreturn= LCD_OK;
	if (LCDstatus == NULL){
		localreturn=LCD_NULLPTR;

	}
	else {
		* LCDstatus=LCD_State;
	}
	return localreturn;
}

/*****************************************************************************************************************/
static LCD_ERRORSTATE_t LCD_PowerON_Proc (void){
	LCD_ERRORSTATE_t localreturn= LCD_OK;
	UserREQ.State=LCD_REQ_busy;
	u8 idx;
	GPIO_Pinconfig_t LCD_pinHandler;

	for (idx=0;idx<_LCD_PIN_NUMNER;idx++)
	{
		LCD_pinHandler.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
		LCD_pinHandler.GPIO_SPEED=GPIO_SPEED_VERY_HIGH;
		LCD_pinHandler.GPIO_pinnumber=LCDs[idx].pin;
		LCD_pinHandler.GPIO_portnumber=LCDs[idx].port;
		localreturn=Gpio_enuInit(&LCD_pinHandler);
	}
	Current_CursiorPostion.Current_Line_Postion=LCD_DISPLAY_LINE1;
	Current_CursiorPostion.Currrent_Col_Postion=LCD_DISPLAY_COL1;
	return localreturn;
}

static LCD_ERRORSTATE_t LCD_WriteCommand (u8 command){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	u8 idx;
	u32 LCD_pinstate;
	if (LCD_PinEnable==Enable_OFF){
		localreturn=GPIO_SetPin_value(LCDs[RS].port,LCDs[RS].pin,GPIO_VALUE_RESET);

		localreturn |= GPIO_SetPin_value(LCDs[RW].port,LCDs[RW].pin,GPIO_VALUE_RESET);

		for (idx=0;(idx<(_LCD_PIN_NUMNER -control_pins_Num));idx++){

			LCD_pinstate=(command & (1 << idx)) ? GPIO_VALUE_SET : GPIO_VALUE_RESET;

			localreturn=GPIO_SetPin_value(LCDs[idx].port,LCDs[idx].pin,LCD_pinstate);

		}
		LCD_PinEnable=Enable_ON;
		LCD_EnableControl(LCD_PinEnable);
	}

	else{
		LCD_PinEnable=Enable_OFF;
		LCD_disableControl(LCD_PinEnable);
	}
	return localreturn;
}



static LCD_ERRORSTATE_t LCD_WriteData (u8 data){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	u8 idx;
	u32 LCD_pinstate;
	if (LCD_PinEnable==Enable_OFF){
		localreturn=GPIO_SetPin_value(LCDs[RS].port,LCDs[RS].pin,GPIO_VALUE_SET);

		localreturn |= GPIO_SetPin_value(LCDs[RW].port,LCDs[RW].pin,GPIO_VALUE_RESET);
		for (idx=0;(idx<(_LCD_PIN_NUMNER -control_pins_Num));idx++){

			LCD_pinstate=((data & (1 << idx))) ? GPIO_VALUE_SET : GPIO_VALUE_RESET;

			localreturn=GPIO_SetPin_value(LCDs[idx].port,LCDs[idx].pin,LCD_pinstate);

		}
		LCD_PinEnable=Enable_ON;
		LCD_EnableControl(LCD_PinEnable);

	}
	else{
		LCD_PinEnable=Enable_OFF;
		LCD_disableControl(LCD_PinEnable);
	}

	return localreturn;
}

static LCD_ERRORSTATE_t LCD_EnableControl (u32 Enable){
	LCD_ERRORSTATE_t localreturn=LCD_OK;

	localreturn =GPIO_SetPin_value(LCDs[En].port,LCDs[En].pin,Enable);

	return localreturn;

}
static LCD_ERRORSTATE_t LCD_disableControl (u32 Enable){
	LCD_ERRORSTATE_t localreturn=LCD_OK;

	localreturn =GPIO_SetPin_value(LCDs[En].port,LCDs[En].pin,Enable_OFF);

	return localreturn;

}

static LCD_ERRORSTATE_t LCD_ClearScreen_proc (void){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	LCD_WriteCommand(LCD_CLEAR_COMMAND);
	if (LCD_PinEnable==Enable_OFF)
	{
		UserREQ.State=LCD_REQ_ready;
		UserREQ.Type=LCD_NoRequest;
	}
	return localreturn;
}

static LCD_ERRORSTATE_t LCD_SetPostion_help(u8 *ptr_to_DDRAM){
	LCD_ERRORSTATE_t localreturn=LCD_OK;
	u8 locationOn_DDRAM=0;
	switch (UserREQ.Current_Postion.Current_Line_Postion)
	{
	case LCD_DISPLAY_LINE1:
		locationOn_DDRAM=UserREQ.Current_Postion.Currrent_Col_Postion + INDEX_FOR_LINE_1;
		break;
	case LCD_DISPLAY_LINE2:
		locationOn_DDRAM=UserREQ.Current_Postion.Currrent_Col_Postion + INDEX_FOR_LINE_2;
		break;
	case LCD_DISPLAY_LINE3:
		locationOn_DDRAM=UserREQ.Current_Postion.Currrent_Col_Postion + INDEX_FOR_LINE_3;
		break;
	case LCD_DISPLAY_LINE4:
		locationOn_DDRAM=UserREQ.Current_Postion.Currrent_Col_Postion + INDEX_FOR_LINE_4;
		break;
	default :
		break;
	}
	*ptr_to_DDRAM=locationOn_DDRAM;
	return localreturn;

}




/************************************************************************************************************************************************/
/* File             :       LCD.h                                                                                                        */
/* AUTHOR           :       Ahmed Adel                                                                                                       */
/* Origin Date      :       3/26/2024                                                                                                            */
/* SWC              :       Character LCD                                                                                                       */
/************************************************************************************************************************************************/
#include "STD_TYPES.h"
#include "LCD_CFG.h"

#ifndef LCD_H_
#define LCD_H_
/************************************Defines****************************************************/

#define LCD_DISPLAY_LINE1		0
#define LCD_DISPLAY_LINE2		1
#define LCD_DISPLAY_LINE3		3
#define LCD_DISPLAY_LINE4		4

#define LCD_DISPLAY_COL1		0
#define LCD_DISPLAY_COL2		1
#define LCD_DISPLAY_COL3		2
#define LCD_DISPLAY_COL4		3
#define LCD_DISPLAY_COL5		4
#define LCD_DISPLAY_COL6		5
#define LCD_DISPLAY_COL7		6
#define LCD_DISPLAY_COL8		7
#define LCD_DISPLAY_COL9		8
#define LCD_DISPLAY_COL10		9
#define LCD_DISPLAY_COL11		10
#define LCD_DISPLAY_COL12		11
#define LCD_DISPLAY_COL13		12
#define LCD_DISPLAY_COL14		13
#define LCD_DISPLAY_COL15		14
#define LCD_DISPLAY_COL16		15

#define MAX_NUM_OF_LINES 		2

#define MAX_NUM_OF_CHARACTERS 	16


/***********************************Types*******************************************************/
typedef enum {
	LCD_OK,
	LCD_NOK,
	LCD_NULLPTR,


}LCD_ERRORSTATE_t;


typedef struct {
	u32 pin;
	void* port ;

}LCD_CFG_t   ;

/************************************API'S***************************************************/

LCD_ERRORSTATE_t LCD_WriteString_Asynch (char* string,u8 Length);

LCD_ERRORSTATE_t LCD_Init_Asynch (void);

LCD_ERRORSTATE_t LCD_ClearScreen_Asynch (void);

LCD_ERRORSTATE_t LCD_getState (u8 * LCDstatus);

LCD_ERRORSTATE_t LCD_SetCursorPostion_Asynch (u8 PostionX ,u8 PostionY);






#endif /* LCD_H_ */

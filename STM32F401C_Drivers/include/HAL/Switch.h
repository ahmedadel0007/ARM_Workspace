
#ifndef SWITCH_H_
#define SWITCH_H_


#include "std_types.h"
#include "GPIO.h"
#include "Switch_cfg.h"



/********************SWITCH ports********************/

#define SWITCH_PORTA 	(void *)(0x40020000)
#define SWITCH_PORTB	(void *)(0x40020400)
#define SWITCH_PORTC	(void *)(0x40020800)

/********************SWITCH pins********************/

#define SWITCH_PIN0 	0x00000000
#define SWITCH_PIN1 	0x00000001
#define SWITCH_PIN2 	0x00000002
#define SWITCH_PIN3 	0x00000003
#define SWITCH_PIN4 	0x00000004
#define SWITCH_PIN5 	0x00000005
#define SWITCH_PIN6 	0x00000006
#define SWITCH_PIN7 	0x00000007
#define SWITCH_PIN8 	0x00000008
#define SWITCH_PIN9		0x00000009
#define SWITCH_PIN10 	0x0000000A
#define SWITCH_PIN11 	0x0000000B
#define SWITCH_PIN12 	0x0000000C
#define SWITCH_PIN13 	0x0000000D
#define SWITCH_PIN14 	0x0000000E
#define SWITCH_PIN15 	0x0000000F

/********************SWITCH Coneection********************/

#define SWITCH_FLOATING		(u32)0x00000000
#define SWITCH_PULLDOWN 	(u32)0x00010001
#define SWITCH_PULLUP		(u32)0x00020002

/********************SWITCH STATUS********************/

#define SWITCH_PRESSED			0
#define SWITCH_RELEASED			1


typedef enum {
   Switch_OK,
   Switch_NOK,
   Switch_Nullptr,
}Switch_ErrorState_t;
/********************SWITCH APIs Prototypes********************/

Switch_ErrorState_t SWITCH_init (void);

Switch_ErrorState_t SWITCH_GETSTATUS(SWITCHES_enu Switchname , u16* SwitchStatus);




#endif /*SWITCH_H_*/

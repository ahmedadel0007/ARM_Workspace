/************************************************************************************************************************************************/
/* File             :       Registers.h                                                                                                         */
/* AUTHOR           :       Ahmed Adel                                                                                                        */
/* Origin Date      :       2/12/2023                                                                                                           */
/* Description      :       Defines the addresses of the REgisters                                                                              */
/* Target           :       Atmega32                                                                                                            */
/************************************************************************************************************************************************/
#ifndef LIB_REGISTERS_H_
#define LIB_REGISTERS_H_


/************************************************************************************************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * DIO REGISTERS  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/************************************************************************************************************************************************/
#define PORTA_REG	(*((volatile u8*)0x3B))
#define DDRA_REG	(*((volatile u8*)0x3A))
#define PINA_REG	(*((volatile u8*)0x39))

#define PORTB_REG	(*((volatile u8*)0x38))
#define DDRB_REG	(*((volatile u8*)0x37))
#define PINB_REG	(*((volatile u8*)0x36))

#define PORTC_REG	(*((volatile u8*)0x35))
#define DDRC_REG	(*((volatile u8*)0x34))
#define PINC_REG	(*((volatile u8*)0x33))

#define PORTD_REG	(*((volatile u8*)0x32))
#define DDRD_REG	(*((volatile u8*)0x31))
#define PIND_REG	(*((volatile u8*)0x30))


#endif /* 00_LIB_REGISTERS_H_ */
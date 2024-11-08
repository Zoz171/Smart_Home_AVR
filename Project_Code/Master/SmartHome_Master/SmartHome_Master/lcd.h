/*
 * lcd.h
 *
 * Created: 9/4/2023 12:42:56 PM
 *  Author: Lenovo
 */ 

#include "STD_Types.h"
#ifndef LCD_H_
#define LCD_H_

#define data PORTB
#define control PORTA
#define rs PA0
#define rw PA1
#define en PA2
#define clear 0x01

void LCD_init(void);
void Send_Command(uint8 cmd);
void Send_Char(uint8 chr);
void Send_String(const char *str);
void LCD_Sprintf(int num);
void LCD_Gotoxy(uint8 x, uint8 y);       // It's a 1-index function not 0
uint32 IntArr_ToInt(uint32* arr , uint8 n );



#endif /* LCD_H_ */
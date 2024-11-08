/*
 * lcd.c
 *
 * Created: 9/4/2023 12:50:43 PM
 *  Author: Lenovo
 */ 
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "BIT_Math.h"
#include "STD_Types.h"
#include "lcd.h"




void Send_Command(uint8 cmd){
	
	CLR_BIT(control,rs);
	CLR_BIT(control,rw);
	data = cmd;
	SET_BIT(control,en);
	_delay_ms(1);
	CLR_BIT(control,en);
}



void LCD_init(void){
	DDRA = 0xff;
	DDRB = 0xff;
	Send_Command(0x38);    //Initialize LCD 16x2
	Send_Command(0x0C);    //LCD ON , cursor blinking
	Send_Command(0x06);    //Auto Increment cursor (from left to right)
	Send_Command(0x01);    //Clear display
	Send_Command(0x80);    //Return cursor to home position (0,0) --> first line
}

void Send_Char (uint8 chr){
	
	SET_BIT(control,rs);
	CLR_BIT(control,rw);
	data = chr;
	SET_BIT(control,en);
	_delay_ms(1);
	CLR_BIT(control,en);
}

void Send_String(const char *str){
	int i = 0;
	while(str[i] != '\0'){
		Send_Char(str[i]);
		i++;
		_delay_ms(1);
	}	
}

void LCD_Sprintf(int num){
	char buff[256];	
	sprintf(buff,"%d",num);
	Send_String(buff);
}

void LCD_Gotoxy(uint8 x, uint8 y){
	char address = 0;
	y--;
	if(x == 1)
	address = 0x80;        //Cursor at beginning of first line 
	else if(x == 2)
	address = 0xC0;       //Cursor at beginning of second line
	
	address += y;
	Send_Command(address);  

	
}

uint32 IntArr_ToInt(uint32* arr , uint8 n ){
	int k = 0;
	
	for(int i=0;i<n;i++){
		k= k*10 + arr[i];
	}
	return k;
	
}
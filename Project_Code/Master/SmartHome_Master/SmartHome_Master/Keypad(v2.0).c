/*
 * Keypad.c
 *
 * Created: 9/5/2023 5:48:24 PM
 *  Author: Lenovo
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include "BIT_Math.h"
#include "lcd.h"
#include "Keypad.h"
     uint8 keypad[4][4] =    { {7 ,8 ,9 ,'/'}
							,  {4 ,5 ,6 ,'x'}
							,  {1 ,2 ,3 ,'-'}
							,  {'o' , 0 , '=' ,'+'}};

void Pad_init(){
	PAD_DDR = 0xf0;				//First 4 pins are inputs , the latter are outputs
	PAD_PORT = 0xff;            //Pull-up resistors are enabled for input pins
}

uint8 Key_Pressed(){
	uint8 row , col;
	uint8 key;

while(1){
	
	for(col = 4; col < 8; col++){

		
		CLR_BIT(PAD_PORT,col);
		
		for( row = 0; row < 4; row++){
			if(BIT_IS_CLEAR(PAD_PIN,row))
			{
				while(BIT_IS_CLEAR(PAD_PIN,row));
				key = keypad[row][col - 4];
				if (key == 'o')
				Send_Command(clear);
				else
				return key;
			}
		}
				SET_BIT(PAD_PORT,4);
				SET_BIT(PAD_PORT,5);
				SET_BIT(PAD_PORT,6);
				SET_BIT(PAD_PORT,7);
		
	}

}

}


/*
*/


/*while(1)
{
_delay_ms(40);
PORTC=0xEF;                                  // 0xEF = 0b1110 1111   --> if Column 1 is low and corresponding row reads (input) low ,then return a character with respect to the pressed key
if(!(PAD_PIN & 0b00000001)) return 7;
if((PAD_PIN & 0b00000010) == 0) return 4;
if((PAD_PIN & 0b00000100) == 0) return 1;
if((PAD_PIN & 0b00001000) == 0) Send_Command(clear);

PORTC=0xDF;                                 //  0xDF = 0b1101 1111    (First 4 pins is connected to columns of keypad respectively and assigned as output)

if((PAD_PIN & 0b00000001) == 0) return 8;
if((PAD_PIN & 0b00000010) == 0) return 5;
if((PAD_PIN & 0b00000100) == 0) return 2;
if((PAD_PIN & 0b00001000) == 0) return 0;

PORTC=0xBF;

if((PAD_PIN & 0b00000001) == 0) return 9;
if((PAD_PIN & 0b00000010) == 0) return 6;
if((PAD_PIN & 0b00000100) == 0) return 3;
if((PAD_PIN & 0b00001000) == 0) return '=';

PORTC=0x7F;

if((PAD_PIN & 0b00000001) == 0) return '/';
if((PAD_PIN & 0b00000010) == 0) return 'x';
if((PAD_PIN & 0b00000100) == 0) return '-';
if((PAD_PIN & 0b00001000) == 0) return '+';

_delay_ms(40);

}*/
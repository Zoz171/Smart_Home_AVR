/*
 * main.c
 *
 * Created: 9/20/2023 6:17:04 PM
 *  Author: Lenovo
 */ 
#define F_CPU 8000000
#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "BIT_Math.h"
#include "STD_Types.h"
#include "Keypad.h"
#include "Timer.h"
#include "USART.h"
#include "Interrupt.h"
#include "lcd.h"

#define START PD5
#define BUZ_DIR DDRD
#define BUZ_PORT PORTD
#define BUZZER 6


volatile uint8 TimerOVFCounter = 0;
volatile uint8 seconds = 0;             //Its a uint32 (unsigned int) because its passed to a "sprintf" function which must take an integer value and return a string
volatile uint8 minutes = 59;
volatile uint8 hours = 12;
volatile uint8 i = 0;
const char *shift[] = {"AM","PM"};
uint32 new_seconds[] = {0,0};
uint32 new_minutes[] = {0,0};
uint32 new_hours[] = {0,0};
uint32 PW = 1555;
	
ISR(INT0_vect){
	Send_Command(clear);
	_delay_ms(250);
	Send_String("...Resetting...");
	_delay_ms(250);
	Send_Command(clear);
	_delay_ms(250);
	Send_String("00");
	Send_Char(':');
	Send_String("00");
	LCD_Gotoxy(1,1);
	
	for(int i = 0; i<2; i++){
		if (i == 0)
		{new_hours[i] = Key_Pressed();
			LCD_Sprintf(new_hours[i]);
			_delay_ms(200);
		}
		else if (i == 1)
		{new_hours[i] = Key_Pressed();
			LCD_Sprintf(new_hours[i]);
		_delay_ms(200);}
		
	}
	
	LCD_Gotoxy(1,4);
	
	for(int j = 0; j<2; j++){
		if (j == 0)
		{new_minutes[j] = Key_Pressed();
			LCD_Sprintf(new_minutes[j]);
			_delay_ms(200);
		}
		else if (j == 1)
		{new_minutes[j] = Key_Pressed();
			LCD_Sprintf(new_minutes[j]);
		_delay_ms(200);}
		
	}
	hours = IntArr_ToInt(new_hours , 2);
	minutes = IntArr_ToInt(new_minutes , 2);
	if(hours > 12)
	hours -= 12;
	if(minutes >= 60)
	minutes = 0;
	
	seconds = 0;
	_delay_ms(150);
	
	Send_Command(clear);
	
	Send_String(" 1: AM  2: PM");
	if(Key_Pressed() == 1)
	{i = 0;}
	
	else if(Key_Pressed() == 2)
	{i = 1;}

	else
	{
		Send_Command(clear);
		_delay_ms(250);
		Send_String("Invalid input");
		_delay_ms(500);
	}
	Send_Command(clear);
	_delay_ms(250);
	Send_String("Starting...");
	_delay_ms(500);
	Send_Command(clear);

}	
	
	
ISR(TIMER0_OVF_vect){
	TimerOVFCounter++;
	
	if(TimerOVFCounter == 29){
		seconds++;
		TimerOVFCounter = 0;
		TIFR = 0x01;			//Clear timer interrupt flag
		
	}
	if (seconds == 60){
		seconds = 0;
		minutes++;
	}
	if (minutes == 60){
		minutes = 0;
		hours++;
	}
	if (hours > 12){
		hours = 1;
		if (i == 0)
		i = 1;
		else if (i == 1)
		i = 0;
	}
}


int main(void)
{
	SET_BIT(PORTD,START);				//Initialize Start button
	uint8 tries = 4;
	uint32 entered_password[4];
	uint8 Block_timer = 10;
	SET_BIT(BUZ_DIR,BUZZER);
	uint32 Temp_Set[] = {2 , 4};
	uint8 Return_flag_1 = 0;
	uint8 Return_flag_2 = 0;
	uint8 Lock_Screen = 0;
	SET_BIT(DDRD,PD7);
	
	LCD_init();
	Pad_init();
	Timer0_OVF_init();
	INT0_Fall_init();	
	USART_init(9600);
	
	while(1){
		 Lock_Screen = 0;
		 CLR_BIT(PORTD,PD7);
		_delay_ms(100);
		Send_Command(clear);
		_delay_ms(100);


	do{
		if(hours < 10)
		{
			LCD_Gotoxy(1,5);
			Send_Char('0');
		}
		else{
			LCD_Gotoxy(1,5);
		}
		LCD_Sprintf(hours);
		
		Send_Char(':');					//
		
		if(minutes < 10)
		{
			LCD_Gotoxy(1,8);
			Send_Char('0');
		}
		else{
			LCD_Gotoxy(1,8);
		}
		LCD_Sprintf(minutes);
		
		Send_Char(':');					//
		
		if(seconds < 10)
		{
			LCD_Gotoxy(1,11);
			Send_Char('0');
		}
		else{
			LCD_Gotoxy(1,11);
		}
		LCD_Sprintf(seconds);

		LCD_Gotoxy(1,1);
		Send_String("    ");
		LCD_Gotoxy(1,13);
		Send_Char(' ');
		
		_delay_ms(8);
		
		LCD_Gotoxy(1,15);
		Send_String(shift[i]);
		
		LCD_Gotoxy(2,1);
		Send_String("21 Sept. 2023");
		
	}while(BIT_IS_SET(PIND,START));
	
	
	while(BIT_IS_CLEAR(PIND,START));			//Wait till start button is released
	
	
	while(Lock_Screen != 1)
	{

	_delay_ms(100);
	Send_Command(clear);
	_delay_ms(100);
	
	while(tries > 0)
	{
		Send_String("Enter Password :");
		LCD_Gotoxy(2,1);
		for(int i = 0; i < 4; i++)
		{
			entered_password[i] = Key_Pressed();
			Send_Char('*');
			
		}

		if(IntArr_ToInt(entered_password,4) == PW)
		{
			Send_Command(clear);
			_delay_ms(500);
			Send_String("Correct Password!");
			SET_BIT(PORTD,PD7);
			_delay_ms(500);
			break;
			
		}
		
		else
		{
			Send_Command(clear);
			_delay_ms(500);
			Send_String("Access Denied");
			_delay_ms(500);
			tries--;
			Send_Command(clear);
			_delay_ms(500);
			Send_String("You Have   tries");
			LCD_Gotoxy(1,10);
			LCD_Sprintf(tries);
			_delay_ms(1000);
			Send_Command(clear);
			_delay_ms(500);
			
		}
		
		if (tries == 0)
		{
			Send_String("You Have Been");
			LCD_Gotoxy(2,1);
			Send_String("blocked for ");
			
			while(Block_timer >= 0 && Block_timer != 255)
			{
				if (Block_timer < 10)
				{
					LCD_Gotoxy(2,14);
					Send_Char(' ');
					LCD_Gotoxy(2,13);
				}
				else
				{LCD_Gotoxy(2,13);}
				
				LCD_Sprintf(Block_timer);
				SET_BIT(BUZ_PORT,BUZZER);
				_delay_ms(1000);
				
				Block_timer--;
			}
			CLR_BIT(BUZ_PORT,BUZZER);
			Send_Command(clear);
			_delay_ms(500);
			Block_timer = 10;
			tries = 4;	
		}
		
	}
	Send_Command(clear);
	_delay_ms(500);

	Send_String("Welcome User");
	_delay_ms(1000);
	Send_Command(clear);
	_delay_ms(500);
	
	 do
	 {
		 
		 Send_Command(clear);
		 _delay_ms(100);
		 Send_Command(clear);
		 _delay_ms(100);
		 Send_String("1:Room1 2:Room2");
		 LCD_Gotoxy(2,1);
		 Send_String("3:Room3 4:More");
		 
		 switch(Key_Pressed())
		 {
			 case 1:
			 _delay_ms(100);
			 Send_Command(clear);
			 _delay_ms(100);
			 Send_String("Choose Mode:");
			 LCD_Gotoxy(2,1);
			 Send_String("1-ON  2-OFF");
			 
			 uint8 mode_1 = Key_Pressed();
			 
			 if(mode_1 == 1)
			 TransmitByte('1');
			 
			 else if(mode_1 == 2)
			 TransmitByte('5');
			 
			 _delay_ms(100);
			 Send_Command(clear);
			 _delay_ms(100);
			 break;
			 
			 case 2:
			 _delay_ms(100);
			 Send_Command(clear);
			 _delay_ms(100);
			 Send_String("Choose Mode:");
			 LCD_Gotoxy(2,1);
			 Send_String("1-ON  2-OFF");
			 
			 uint8 mode_2 = Key_Pressed();
			 
			 if(mode_2 == 1)
			 TransmitByte('2');
			 
			 else if(mode_2 == 2)
			 TransmitByte('6');
			 
			 _delay_ms(100);
			 Send_Command(clear);
			 _delay_ms(100);
			 break;
			 
			 case 3:
			 _delay_ms(100);
			 Send_Command(clear);
			 _delay_ms(100);
			 Send_String("Choose Mode:");
			 LCD_Gotoxy(2,1);
			 Send_String("1-ON  2-OFF");
			 
			 uint8 mode_3 = Key_Pressed();
			 
			 if(mode_3 == 1)
			 TransmitByte('3');
			 
			 else if(mode_3 == 2)
			 TransmitByte('7');
			 
			 _delay_ms(100);
			 Send_Command(clear);
			 _delay_ms(100);
			 break;
			 
			 case 4:
			 do
			 {
				 Send_Command(clear);
				 _delay_ms(100);
				 
				  if(Lock_Screen == 1)
				  break;
				 
				 Send_String("1:AC");
				 LCD_Gotoxy(1,12);
				 Send_String("2:TV");
				 LCD_Gotoxy(2,1);
				 Send_String("3:Return");
				 LCD_Gotoxy(2,11);
				 Send_String("4:More");
				 
				 switch(Key_Pressed())
				 {
					 case 1:
					 
					 Send_Command(clear);
					 _delay_ms(100);
					 Send_String("Set Temp. = __ C");
					 LCD_Gotoxy(1,13);
					 for(int i = 0; i < 2; i++)
					 {
						 Temp_Set[i] = Key_Pressed();
						 LCD_Sprintf(Temp_Set[i]);
					 }
					 
					 uint8 Sent_Temp = IntArr_ToInt(Temp_Set,2);
					 TransmitByte(Sent_Temp);
					 
					 Send_Command(clear);
					 _delay_ms(100);
					 Send_String("Saved !");
					 _delay_ms(500);
					 break;
					 
					 case 2:
					 _delay_ms(100);
					 Send_Command(clear);
					 _delay_ms(100);
					 Send_String("Choose Mode:");
					 LCD_Gotoxy(2,1);
					 Send_String("1-ON  2-OFF");
					 uint8 mode_4 = Key_Pressed();
					 
					 if(mode_4 == 1)
					 TransmitByte('T');
					 
					 else if(mode_4 == 2)
					 TransmitByte('V');
					 break;
					 
					 case 3:
					 Return_flag_1 = 1;
					 break;
					 
					 case 4:
					 do{
					  _delay_ms(100);
					  Send_Command(clear);
					  _delay_ms(100);
					  if(Lock_Screen == 1)
					  break;
					  
					  LCD_Gotoxy(1,1);
					  Send_String("1:LockScreen");
					  LCD_Gotoxy(2,1);
					  Send_String("2:Return");
					  uint8 Status = Key_Pressed();
					  
					  if(Status == 1)
					  Lock_Screen = 1;
					  else if(Status == 2)
					  Return_flag_2 = 1;
						  
					  }while(Return_flag_2 != 1);
					 
					 break;
					 
				 }
				 Return_flag_2 = 0;
				 
			 }while(Return_flag_1 != 1);
			 
			 Return_flag_1 = 0;
			 
			 break;
			 
			 default:
			 Send_Command(clear);
			 _delay_ms(100);
			 Send_String("Invalid Input");
			 _delay_ms(500);
			 Send_Command(clear);
			 _delay_ms(100);
			 break;
		 }
		 
	 }while(Lock_Screen != 1);
	 
	}
	
  }
  
}

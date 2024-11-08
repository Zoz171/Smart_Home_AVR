/*
 * main.c
 *
 * Created: 9/17/2023 1:17:26 PM
 *  Author: Lenovo
 */ 
#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BIT_Math(v2.0).h"
#include "STD_Types.h"
#include "USART.h"
#include "ADC.h"
#include "Timer.h"
uint16 Temp = 0;
uint16 Sensor_Reading = 0;
uint8 counter = 0;

ISR(TIMER0_OVF_vect)
{
	counter++;
	Sensor_Reading = ADC_Read(0) / 2.0;
	
	if(counter > 2)
	{
		counter = 0;
		if(Temp < Sensor_Reading)
		SET_BIT(PORTC,PC3);
		else
		CLR_BIT(PORTC,PC3);
		
	}
	
}
	

int main(void)
{

	ADC_init();
	USART_init(9600);
	Timer0_OVF_init();
	DDRC = 0xff;
	uint8 Byte = 0;
	
    while(1)
    {
		
		Byte = RecieveByte();
		
		if(Byte >= 14 && Byte <= 35)
		{
			Temp = Byte;
		}
		
		
		else
		{
		
		switch(Byte)
		{
			case '1':
			SET_BIT(PORTC,PC0);
			break;
			
			case '2':
			SET_BIT(PORTC,PC1);
			break;
			
			case '3':
			SET_BIT(PORTC,PC2);
			break;
			
			case '5':
			CLR_BIT(PORTC,PC0);
			break;
			
			case '6':
			CLR_BIT(PORTC,PC1);
			break;
			
			case '7':
			CLR_BIT(PORTC,PC2);
			break;
			
			case 'T':
			SET_BIT(PORTC,PC4);
			break;
			
			case 'V':
			CLR_BIT(PORTC,PC4);
			break;
			
			
		}
		}
	}
        
    }
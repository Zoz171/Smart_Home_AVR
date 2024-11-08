/*
 * ADC.c
 *
 * Created: 9/19/2023 1:20:57 PM
 *  Author: Lenovo
 */ 
#include <avr/io.h>
#include "BIT_Math(v2.0).h"
#include "STD_Types.h"
#include "ADC.h"

void ADC_init(){
	SET_BIT(ADCSRA , ADEN);						//enable ADC
	
	SET_BIT(ADMUX , REFS0);						//Voltage reference is AVCC with external capacitor at AREF pin
	
	SET_BIT(ADCSRA ,ADPS0);						//prescaler of 128			//ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	SET_BIT(ADCSRA ,ADPS1);
	SET_BIT(ADCSRA ,ADPS2);
}

uint32 ADC_Read(uint8 channel){
	
	ADMUX |= (channel & 0x0F);
	
	SET_BIT(ADCSRA , ADSC);
	while(BIT_IS_CLEAR(ADCSRA , ADIF));
	
	return ADC;
}

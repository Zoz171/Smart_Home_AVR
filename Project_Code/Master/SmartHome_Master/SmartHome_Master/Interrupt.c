/*
 * Interrupt.c
 *
 * Created: 9/7/2023 12:00:33 PM
 *  Author: Lenovo
 */ 
#include "Interrupt.h"
#include "BIT_Math.h"
#include <avr/io.h>
#include <avr/interrupt.h>



void INT0_Fall_init(){
	SET_BIT(DDRD,PD2);
	SET_BIT(PORTD,PD2);
	SET_BIT(GICR,INT0);
	SET_BIT(MCUCR,ISC01);
	sei();
	
}
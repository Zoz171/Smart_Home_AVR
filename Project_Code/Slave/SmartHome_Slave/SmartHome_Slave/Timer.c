/*
 * Timer.c
 *
 * Created: 9/4/2023 8:58:43 PM
 *  Author: Lenovo
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "BIT_Math(v2.0).h"

void Timer0_OVF_init(void){
	TCCR0 |= (1<<CS02) | (1<<CS00);
	TCNT0 = 0x01;
	sei();
	TIMSK |= (1<<TOIE0);
	
}

void Timer1_CTC_init(){
	SET_BIT(TCCR1B , CS12);					//clk prescalar = 1024;
	SET_BIT(TCCR1B , CS10);
	
	SET_BIT(TCCR1B , WGM12);
	
	TCNT1 = 0;
	OCR1A = 7780;							// approximately 1 second (Compare register is continuously compared with TCNT1 until matching , then OCF1A is set)
	
	SET_BIT(TIMSK , OCIE1A);
	sei();
	
	
}
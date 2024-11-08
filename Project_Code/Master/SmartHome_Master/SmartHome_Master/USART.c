/*
 * USART.c
 *
 * Created: 9/17/2023 12:03:23 PM
 *  Author: Lenovo
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "USART.h"
#include "STD_Types.h"
#include "BIT_Math.h"
 

void USART_init(uint32 baud)
{
	SET_BIT(UCSRB , TXEN);					//enabling transmitter and receiver in uart
	SET_BIT(UCSRB , RXEN);
	
	SET_BIT(UCSRC , URSEL);					//Character (data) size of 8-bit
	SET_BIT(UCSRC , UCSZ0);
	SET_BIT(UCSRC , UCSZ1);
	
	UBRRL = (( F_CPU / (16UL*baud) )-1);
	UBRRH = 0;
}

void TransmitByte(uint8 data){
	
	/* Wait for empty transmit buffer */
	while (BIT_IS_CLEAR(UCSRA , UDRE));
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

uint8 RecieveByte(void){
	/* Wait for data to be received */
	while (BIT_IS_CLEAR(UCSRA , RXC));
	;
	/* Get and return received data from buffer */
	return UDR;
}
	
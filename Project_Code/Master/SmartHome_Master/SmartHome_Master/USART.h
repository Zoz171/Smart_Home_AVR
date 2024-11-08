/*
 * USART.h
 *
 * Created: 9/17/2023 11:59:56 AM
 *  Author: Lenovo
 */ 


#ifndef USART_H_
#define USART_H_
#include "STD_Types.h"

void USART_init(uint32 baud);
void TransmitByte(uint8 data);
uint8 RecieveByte(void);



#endif /* USART_H_ */
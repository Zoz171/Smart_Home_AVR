/*
 * 
 *
 * Created: 9/5/2023 5:43:08 PM
 *  Author: Lenovo
 */ 

#include "STD_Types.h"
#include <avr/io.h>
#ifndef KEYPAD_H_
#define KEYPAD_H_

#define PAD_DDR DDRC
#define PAD_PORT PORTC
#define PAD_PIN PINC


uint8 Key_Pressed(void);
void Pad_init();



#endif /* INCFILE1_H_ */
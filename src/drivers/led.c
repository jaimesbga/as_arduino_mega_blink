/*
 * led.c
 *
 * Created: 3/30/2020 10:40:51 AM
 *  Author: Test
 */ 

#include "led.h"
#include <avr/io.h>

#define PORT_LED	DDRB
#define MASK_LED	0B10000000	

void led_set_status(uint8_t uValue){	
	if(uValue == LED_OFF)
		PORT_LED &= ~MASK_LED;
	else
		PORT_LED|=MASK_LED;
}

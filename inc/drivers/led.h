/*
 * led.h
 *
 * Created: 3/30/2020 10:41:09 AM
 *  Author: Test
 */ 


#ifndef LED_H_
#define LED_H_

#include <stdint.h>

enum{
	LED_OFF = 0,
	LED_ON		
};

void led_set_status(uint8_t uValue);

#endif /* LED_H_ */
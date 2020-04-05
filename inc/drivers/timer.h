/*
 * usart.h
 *
 * Created: 3/30/2020 11:10:35 AM
 *  Author: Test
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

enum{
	TICK_1_SEG,
	TICK_10_SEG		
};

void TIMER_Init( void );
uint8_t timer_check(uint8_t uflag);

#endif

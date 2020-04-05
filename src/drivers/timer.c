/*
 * timer.c
 *
 * Created: 3/30/2020 10:40:51 AM
 *  Author: Test
 */ 
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define __disable_irq() cli();	
#define __enable_irq() sei();

static uint8_t __counter_1s;
static uint8_t __flag_1s;

static uint8_t __counter_10s;
static uint8_t __flag_10s;

void TIMER_Init( void )
{
	//Disable global interruptions
	__disable_irq();	
	// Set 0x00 Register A and B for timer 1
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1  = 0x00;
	//http://www.arduinoslovakia.eu/application/timer-calculator	
	// 10 Hz (16000000/((6249+1)*256))
	OCR1A = 6249; //Set Counter 
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 256
	TCCR1B |= (1 << CS12);
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
	
	__counter_1s	= 0;
	__flag_1s		= 0;
	__counter_10s	= 0;
	__flag_10s		= 0;
	//Enable global interruptions
	__enable_irq();
}

ISR(TIMER1_COMPA_vect)
{	
	if(__counter_1s++ == 10){
		__counter_1s = 0;
		__counter_10s++;
		__flag_1s = 1;		
	}	
	
	if(__counter_10s == 10){
		__counter_10s = 0;
		__flag_10s =  1;
	}
}

uint8_t timer_check(uint8_t uflag)
{	
	uint8_t uResp = 0;		
	switch(uflag)
	{
		case TICK_1_SEG:{
			uResp = __flag_1s;
			__flag_1s = 0;			
		}break; 
		case TICK_10_SEG:{
			uResp = __flag_10s;
			__flag_10s = 0;
			}break;
	}//switch(uflag)	
	return uResp;
}


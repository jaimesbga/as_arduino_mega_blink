#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DELAY_BLINK 100

int main(void)
{
	DDRB |= 0B10000000;
    while (1) 
    {
		DDRB |= 0B010000000;
		_delay_ms(DELAY_BLINK);
		DDRB &= 0B01111111;
		_delay_ms(DELAY_BLINK);
    }
}


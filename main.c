#define F_CPU 16000000UL

#include <util/delay.h>
#include "inc/common.h"

#define DELAY_BLINK 50

int main(void)
{
	
	led_set_status(LED_ON);
	
    while (1) 
    {
		led_set_status(LED_OFF);
		_delay_ms(DELAY_BLINK);
		led_set_status(LED_ON);
		_delay_ms(DELAY_BLINK);
    }
}


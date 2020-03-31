#include "inc/common.h"
#include <util/delay.h>
#include <stdio.h>

#define DELAY_BLINK 50

void InitDevice( void ){	
	/* Initialize USART */	
	USART_Init();
	/* Set Led OFF */
	led_set_status(LED_OFF);
}

int main(void)
{
	uint8_t _flag_message = 0;
	
	InitDevice();		
    while (1) 
    {		
		_flag_message = _flag_message + 1;
		if(_flag_message == 5){
			led_set_status(LED_ON);
			printf("Hello World\n");
			_flag_message = 0;			
			_delay_ms(DELAY_BLINK);
		}	
		else{
			led_set_status(LED_OFF);
			_delay_ms(DELAY_BLINK);
		}
    }//while (1) 
}


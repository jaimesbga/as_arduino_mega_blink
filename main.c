#include "inc/common.h"
#include <util/delay.h>
#include <stdio.h>

#define DELAY_BLINK 10

void InitDevice( void ){
	
	/* Set Led OFF */
	led_set_status(LED_OFF);	
	
	/* Set Timers */
	TIMER_Init();
	
#if USE_ST7735_TFT18	
	/* Initialize ST7735 TFT 1.8 */	
	St7735Init();	
#endif	
	/* Initialize USART */	
	USART_Init();

}

int main(void)
{
	InitDevice();		
    while (1) 
    {		
		if(timer_check(TICK_1_SEG)){
			led_set_status(LED_ON);	
			_delay_ms(DELAY_BLINK);
			printf("Hello World\n");			
		}//if(timer_check(TICK_10_SEG))
		else{
			led_set_status(LED_OFF);
			_delay_ms(DELAY_BLINK);
		}
    }//while (1) 
}


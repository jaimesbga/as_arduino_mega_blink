#include "avr/io.h"
#include "usart.h"

#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define UBRR_VAL (FOSC/16/BAUD-1)

#define _USE_DIRECTLY_REG	0
#define _CONFIGURE_PRINTF	1

#if _CONFIGURE_PRINTF 
	#include <stdio.h>
	static int usart_putchar_printf(char var, FILE *stream);
	static FILE avr_stdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);
#endif 

#if _USE_DIRECTLY_REG == 0
typedef struct _usart_port{
	 volatile uint8_t * REG_H_BR;
	 volatile uint8_t * REG_L_BR;
	 volatile uint8_t * REG_UC_B;
	 volatile uint8_t * REG_UC_C;
	 volatile uint8_t * REG_UC_A;
	 volatile uint8_t * REG_UDR;
	 /* Registers*/
	 uint8_t RXENn;
	 uint8_t TXENn;
	 uint8_t USBSn;
	 uint8_t UCSZn1;
	 uint8_t UCSZn0;
	 uint8_t UDREn;
}tPort;

tPort __USB_PORT = {
	.REG_H_BR	= &UBRR0H,	.REG_L_BR	= &UBRR0L,	.REG_UC_B	= &UCSR0B,
	.REG_UC_C	= &UCSR0C,	.REG_UC_A	= &UCSR0A,	.REG_UDR	= &UDR0,
	.RXENn		= RXEN0,	.TXENn		= TXEN0,	.USBSn		= USBS0,
	.UCSZn1		= UCSZ01,	.UCSZn0		= UCSZ00,	.UDREn		= UDRE0,
};
tPort * usart_current = &__USB_PORT;
#endif

void USART_Init( void ){
		
#if _USE_DIRECTLY_REG == 0			
	/* Set baud rate */
	*(usart_current->REG_H_BR) = UBRR_VAL>>8;
	*(usart_current->REG_L_BR) = UBRR_VAL; 	
	/* Enable UART receiver and transmitter */
	*(usart_current->REG_UC_B) = ((1<<usart_current->RXENn)|(1<<usart_current->TXENn));		
	/* Set frame format: 8 data 1 stop */
	*(usart_current->REG_UC_C) = (0<<usart_current->USBSn)|(1<<usart_current->UCSZn1)|(1<<usart_current->UCSZn0);	
#else
		/* Set baud rate */
		UBRR0H = (uint8_t) (UBRR_VAL>>8);
		UBRR0L = (uint8_t) UBRR_VAL;
		/* Enable UART receiver and transmitter */
		UCSR0B = ((1<<RXEN0)|(1<<TXEN0));
		/* Set frame format: 8 data 2stop */
		UCSR0C = (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
#endif	
#if _CONFIGURE_PRINTF 
    // setup our stdio stream
    stdout = &avr_stdout;
#endif 	
}

void USART_Transmit( uint8_t data )
{
#if _USE_DIRECTLY_REG == 0	
	/* Wait for empty transmit buffer */
	while ( !( *(usart_current->REG_UC_A) & (1<<usart_current->UDREn)) )
	;
	/* Put data into buffer, sends the data */
	*(usart_current->REG_UDR)  = data;
#else
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0  = data;
#endif	
}

#if _CONFIGURE_PRINTF
int usart_putchar_printf(char var, FILE *stream) {
	if (var == '\n') USART_Transmit('\r');
	USART_Transmit(var);
	return 0;
}
#endif 
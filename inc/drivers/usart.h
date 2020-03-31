/*
 * usart.h
 *
 * Created: 3/30/2020 11:10:35 AM
 *  Author: Test
 */ 


#ifndef USART_H_
#define USART_H_

#include <stdint.h>

void USART_Init( void );
void USART_Transmit( uint8_t data );

#endif /* USART_H_ */
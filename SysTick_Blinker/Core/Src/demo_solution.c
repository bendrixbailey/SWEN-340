/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: larry kiser
 */

#include <stdio.h>
#include <string.h>

#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "stm32l4xx.h"


static void demo_of_printf_scanf(){
	char rxByte;
	char *prompt = "Give Red LED control input (Y = On, N = off):\r\n" ;
	char *LED_off = "LED is Off\r\n\r\n" ;
	char *LED_on = "LED is On\r\n\r\n" ;

	USART_Write( USART2, (uint8_t *)prompt, strlen( prompt ) ) ;
	scanf ("%c", &rxByte);

	if (rxByte == 'N' || rxByte == 'n'){
		LED_Off();
		USART_Write( USART2, (uint8_t *)LED_off, strlen( LED_off ) ) ;
	}
	else if (rxByte == 'Y' || rxByte == 'y'){
		LED_On();
		USART_Write( USART2, (uint8_t *)LED_on, strlen( LED_on ) ) ;
	}
}

static void delay_loop( int value )
{
	// spin loop consuming CPU to spend time.
	for (int i = 0; i < 8000000; i++)
		;
}

static void init_systick()
{
	SysTick->CTRL = 0 ;
	SysTick->LOAD = 8000000 ;	// 16 million clock ticks
	SysTick->CTRL |= 4 ;		// set clock source to internal
	SysTick->CTRL |= 1 ;		// enable the SysTick clock
}

static void delay_systick()
{
	for ( int i = 0 ; i < 10 ; i++ )
		while ( ( SysTick->CTRL & 0x10000 ) == 0 )
			;
}

//static void demo_of_UART_print(int a){
//	int n ;
//	float b;
//	uint8_t buffer[BUFFER_SIZE];
//
//	b = (float)a/100;
//	n = sprintf((char *)buffer, "a = %d\t", a);
//	n += sprintf((char *)buffer + n, "b = %f\r\n", b);
//	USART_Write(USART2, buffer, n);
//
//	//delay_loop( 8000000 ) ;
//	delay_systick() ;
//
//	LED_Toggle();
//}

//void run_demo(){
//	int a = 0;
//
//	init_systick() ;
//
//	while (1){
//		//demo_of_printf_scanf();
//		demo_of_UART_print(a);
//		a++;
//	}
//}


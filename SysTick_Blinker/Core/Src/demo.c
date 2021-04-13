/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: Bendrix bailey
 */

#include <stdio.h>
#include <string.h>

#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "stm32l4xx.h"

static void delay_loop( int value )
{
	// spin loop consuming CPU to spend time.
	for (int i = 0; i < value; i++)
		;
}

static void init_systick()
{
	// Use the SysTick global structure pointer to do the following in this
	// exact order with separate lines for each step:
	//
	// Disable SysTick by clearing the CTRL (CSR) register.
	// Set the LOAD (RVR) to 8 million to give us a 100 milliseconds timer.
	// Set the clock source bit in the CTRL (CSR) to the internal clock.
	// Set the enable bit in the CTRL (CSR) to start the timer.
	SysTick->CTRL = 0 ; 	//Clear CSR register
	SysTick->LOAD = 8000000 ;	//Set RVR to 8 mil
	SysTick->CTRL |= 4 ;		//set clock source to internal board clock
	SysTick->CTRL |= 1 ;		//turn on systick clock
}

static void delay_systick()
{
	// Using the SysTick global structure pointer do the following:
	// Create a for loop that loops 10 times
	// Inside that for loop check the COUNTFLAG bit in the CTRL (CSR)
	// register in a loop. When that bit is set exit this inner loop
	// to do another pass in the outer loop of 10.
	for ( int i = 0 ; i < 10 ; i++ )
			while ( ( SysTick->CTRL & 0x10000 ) == 0 )	//checks countflag bit, count down.
				;
}

static void demo_of_UART_print(int a){
	int n ;
	uint8_t buffer[BUFFER_SIZE];

	n = sprintf((char *)buffer, "a = %d\r\n", a);
	USART_Write(USART2, buffer, n);

	//delay_loop( 8000000 ) ;	// comment this out when you are ready to test delay_systick
	delay_systick() ;	// enable this when you are ready to test

	LED_Toggle();
}

void run_demo(){
	int a = 0;

	init_systick() ;

	while (1){
		//demo_of_printf_scanf();
		demo_of_UART_print(a);
		a++;
	}
}


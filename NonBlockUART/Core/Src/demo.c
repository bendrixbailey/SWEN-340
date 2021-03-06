/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: larry kiser
 *      Editor: bendrix bailey
 *  Update to starter code for non-blocking assignment.
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
	// Set the LOAD (RVR) to 80,000 to give us a 1 millisecond timer.
	// Set the clock source bit in the CTRL (CSR) to the internal clock.
	// Set the enable bit in the CTRL (CSR) to start the timer.
	SysTick->CTRL = 0 ;
	SysTick->LOAD = 80000 ;	//Set RVR to 80,000
	SysTick->CTRL |= 4 ;	//set clock source to internal board clock
	SysTick->CTRL |= 1 ;	//turn on systick clock
}

static void delay_systick()
{
	// Using the SysTick global structure pointer do the following:
	// Check for the COUNTFLAG to be set. Return as soon as it is set.
	// This loop for the COUNTFLAG is a blocking call but not for more than 1 millisecond.
	while(! ( SysTick->CTRL & 0x10000 ) == 1 );
	return;
}


void run_demo()
{
	//uint8_t buffer[BUFFER_SIZE];
	uint8_t one_char = 0 ;

	init_systick() ;

	while (1)
	{
		// Change this to delay of only 1 millisecond.
		// After calling this 1000 times then do the LED Toggle.
		// delay_loop( 8000000 ) ;	// comment this out when you are ready to test delay_systick
		for(int i = 0; i < 1000; i++){
			delay_systick();
			//delay_loop(80000);
		}
		// delay_systick() ;	// enable this when you are ready to test

		one_char = USART_Read_Nonblocking( USART2 ) ;	// change this to a non-blocking call
		// Only echo the character if we got a character
		// If we get an Enter key then also write out a '\n'
		USART_Write( USART2, &one_char, 1 ) ;
		//if 1 second elapsed, toggle led, reset/clear toggle
		LED_Toggle();
	}
}


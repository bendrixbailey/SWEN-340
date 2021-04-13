//Main file for API functions, also contains main API loop

#include <string.h>
#include <stdio.h>

#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"


static uint8_t one_second_elapsed;
static uint8_t green_flash;
static uint8_t red_flash;

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
	SysTick->CTRL |= 2;
}

static void delay_systick()
{
	// Using the SysTick global structure pointer do the following:
	// Check for the COUNTFLAG to be set. Return as soon as it is set.
	// This loop for the COUNTFLAG is a blocking call but not for more than 1 millisecond.
	while(! ( SysTick->CTRL & 0x10000 ) == 1 );
	return;
}

static void print_intro(){
	//This function handles the printing of the introduction and available commands
	char *doc1 = "\r\nLED Blinker demo. Commands are as follows:\r\n" ;
	char *doc2 = "\r\nRON | ROFF | RFLASH\r\n GON | GOFF| GFLASH\r\n FLASHOFF\r\n";
	char *doc3 = "\r\nPressing ENTER after a full command has\r\n been entered will execute command.\r\n";

	USART_Write(USART2, (uint8_t *)doc1, strlen(doc1));
	USART_Write(USART2, (uint8_t *)doc2, strlen(doc2));
	USART_Write(USART2, (uint8_t *)doc3, strlen(doc3));
}

static void init_all(){
	//init function that should init all necessary stuff.
	LED_Init();
	init_systick();
}

static void process_input(char *buffer){
	//This function processes the input buffer, if its any of the commands, it calls the respective
	//function, otherwise it prints "invalid command"
	if(strcmp(buffer, "RON") == 0){
		LED_r_On();
	}else if (strcmp(buffer, "ROFF") == 0){
		LED_r_Off();
	}else if (strcmp(buffer, "GON") == 0){
		LED_g_On();
	}else if (strcmp(buffer, "GOFF") == 0){
		LED_g_Off();
	}else if (strcmp(buffer, "RFLASH") == 0){
		red_flash = 1;
	}else if (strcmp(buffer, "GFLASH") == 0){
		green_flash = 1;
	}else if (strcmp(buffer, "FLASHOFF") == 0){
		red_flash = 0;
		green_flash = 0;
	}else{
		char *error1 = "\r\nInvalid Command!\r\n";
		USART_Write(USART2, (uint8_t *)error1, strlen(error1));
	}
}

static void toggle_flashing(){
	if(green_flash == 1){
		LED_Toggle_G();
	}
	if(red_flash == 1){
		LED_Toggle_R();
	}
}


void SysTick_Handler()
{
	static uint32_t counter;
	for(counter = 0; counter < 1000; counter ++){
		;
	}
	one_second_elapsed = 1;
	counter = 0;
}


int UpdateApiCheck(){
	uint8_t entryBuffer[BUFFER_SIZE];
	uint8_t index = 0;
	uint8_t r_char;

	init_all();
	print_intro();

	while(1){
		r_char = USART_Read_Nonblocking(USART2); //get character from console

		if(r_char ){
			if (r_char == '\r')
			{
				entryBuffer[index] = '\0';
				index = 0;
				//check full buffer and compare to all possible functions
				process_input((char *)entryBuffer);
				USART_Write(USART2, (uint8_t *)'\n', 1);
				//if none, print out 'invalid command'
			}
			else if(index < BUFFER_SIZE){ //if index is less than buffer,
				entryBuffer[index++] = r_char; //
			}

			if(r_char == 0x7f){
				//backspace, overwrite character
				index --;
				USART_Write(USART2, entryBuffer, index);
			}

			USART_Write(USART2, &r_char, 1); //echo rchar to buffer
			//if enter key, check for valid command
			//if backspace, remove previous char from buffer, display result
			//echo character, add to command buffer
			//backspace is 0x7F
		}

		if(one_second_elapsed)
			//toggle_lines(); // flip led thats on to off, and vice versa
			green_flash = 1;
		one_second_elapsed = 0;
	}

}

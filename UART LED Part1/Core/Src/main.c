// main.c for UART LED project.
// author: bendrix bailey


// include project specific header files
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "LED_API.h"

	
int main(void){

	// initialization code
	System_Clock_Init(); // set System Clock = 80 MHz
	UART2_Init();
	
	// application run function
	UpdateApiCheck();	//calls my fancy function every cycle
}


// main.c with demo
// Updated and refactored Larry Kiser copyright 2021


// include project specific header files
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "LED_API.h"

	
int main(void){

	// initialization code
	System_Clock_Init(); // set System Clock = 80 MHz
	UART2_Init();
	
	// application run function
	UpdateApiCheck();
}


// Create standard project template for STM32L476VG discovery board
// using polling mode UART bare metal functionality.
// Include C language unit testing support.
// Larry L. Kiser Feb. 24, 2019 Rochester Institute of Technology
// Based in substantial part on Dr. Yifeng Zhu's source code.

#include <string.h>
#include <stdio.h>

#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "LED_API.h"
#include "unit_tests.h"

// Only add a call to your main code to this source file.
int main(void)
{
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
	
	// Add your one function call here

}

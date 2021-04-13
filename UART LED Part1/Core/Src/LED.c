#include "LED.h"


//******************************************************************************************
// User LED = LD2 Green LED = PA.5
//******************************************************************************************
#define LED_PIN 5

#define NUCLEO_GREEN_LED_PIN (5)	// GPIO PA5
#define ARDUINO_D12 (6)				// GPIO PA6
#define ARDUINO_D11 (7)				// GPIO PA7

// GPIO Output initialization for GPIO banks A, B, C, and D only
// Expects GPIO to be GPIOA, GPIOB, GPIOC, or GPIOD.
// pin is expected to be 0 through 15
void GPIO_Output_Init( GPIO_TypeDef *GPIO, uint32_t pin )
{
	// Enable the peripheral clocks of for GPIO
	if ( GPIO == GPIOA )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
	else if ( GPIO == GPIOB )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN ;
	else if ( GPIO == GPIOC )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN ;
	else if ( GPIO == GPIOD )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN ;
	else
		return ;

	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIO->MODER &= ~( 3U << ( 2 * pin ) ) ;  // clear to input mode (00)
	GPIO->MODER |= 1U << ( 2 * pin ) ;      //  Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIO->OSPEEDR &= ~( 3U << ( 2 * pin ) ) ;	// set to cleared which is low speed
	GPIO->OSPEEDR |=   3U << ( 2 * pin ) ;  // High speed
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIO->OTYPER &= ~( 1U << pin ) ;       // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIO->PUPDR   &= ~( 3U << ( 2 * pin ) ) ;  // No pull-up, no pull-down

}

// set up PA5, PA6, and PA7 to drive LEDs
void LED_Init(void){
	GPIO_Output_Init( GPIOA, NUCLEO_GREEN_LED_PIN ) ;	// hard wired PA5 to on-board LD2 LED
	GPIO_Output_Init( GPIOA, ARDUINO_D12 ) ;		// init PA6 as output (D12)
	GPIO_Output_Init( GPIOA, ARDUINO_D11 ) ;		// init PA7 as output (D11)
}

//******************************************************************************************
// Turn LED On and GPIOA 6 and 7 to ON
//******************************************************************************************
void LED_r_On(void){
	GPIOA->ODR |= 1UL << NUCLEO_GREEN_LED_PIN ; // PA5
	GPIOA->ODR |= 1UL << ARDUINO_D12 ;	// PA6
}

//******************************************************************************************
// Turn LED Off and GPIOA 6 and 7 to OFF
//******************************************************************************************
void LED_r_Off(void){
	GPIOA->ODR &= ~( 1UL<< NUCLEO_GREEN_LED_PIN );
	GPIOA->ODR &= ~( 1UL << ARDUINO_D12 ) ;	// PA6
}

//******************************************************************************************
// Turn LED On and GPIOA 6 and 7 to ON
//******************************************************************************************
void LED_g_On(void){
	GPIOA->ODR |= 1UL << NUCLEO_GREEN_LED_PIN ; // PA5
	GPIOA->ODR |= 1UL << ARDUINO_D11 ;	// PA7
}

//******************************************************************************************
// Turn LED Off and GPIOA 6 and 7 to OFF
//******************************************************************************************
void LED_g_Off(void){
	GPIOA->ODR &= ~( 1UL<< NUCLEO_GREEN_LED_PIN );
	GPIOA->ODR &= ~( 1UL << ARDUINO_D11 ) ;	// PA7
}

//******************************************************************************************
// Set LD2 Nucleo LED and GPIOA 6 and 7 to opposite states
//******************************************************************************************
void LED_Toggle_R(void){
	GPIOA->ODR ^= 1UL << NUCLEO_GREEN_LED_PIN ;
	GPIOA->ODR ^= 1UL << ARDUINO_D12 ;	// PA6
}

void LED_Toggle_G(void){
	GPIOA->ODR ^= 1UL << ARDUINO_D11 ;	// PA7
}

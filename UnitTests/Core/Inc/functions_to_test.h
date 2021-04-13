// functions_to_test.c
// Larry Kiser Created for the STM32 bare metal environment Feb. 24, 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "stm32l476xx.h"
#include "unit_tests.h"
#include "UART.h"

// Add the function prototypes here for the functions to be tested.

uint32_t example_1( uint32_t input_value ) ;
char *example_2( char *input_string ) ;
uint8_t test_for_bit_value( uint8_t byte_value, uint8_t bit_position ) ;
void swap_case_in_string( char *input_string, char *output_string ) ;

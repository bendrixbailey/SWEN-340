// unit_tests.c
// Larry Kiser Original version October 30, 2015
// Larry Kiser Updated for STM32 bare metal environment Feb. 24, 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "stm32l476xx.h"
#include "unit_tests.h"
#include "UART.h"
#include "functions_to_test.h"

// ST version of printf for STM32L476VG in bare metal mode.
// Does not return a value but otherwise works like printf.
// NOTE -- the max expected formated string is limited. See the buffer definition in the function.
void st_printf( char string_format[], ... )
{
	char buffer[100] ;
	va_list arguments ;
	
	va_start( arguments, string_format ) ;
	vsprintf( buffer, string_format, arguments ) ;		// create the formatted string in buffer -- hope it fits!
	va_end( arguments ) ;
	USART_Write( USART2, (uint8_t *)buffer, strlen( buffer ) ) ;	// now write it out to USART2
}

// Simple boolean assert function for unit testing
int assert( int test_result, char error_format[], ... ) {
	va_list arguments ;
	char buffer[100] ;
	static int test_number = 1 ;
	int result = 1 ;	// return 1 for test passed or 0 if failed
	
	if ( ! test_result ) {
		st_printf( "Test # %d failed: ", test_number ) ;
		va_start( arguments, error_format ) ;
		vsprintf( buffer, error_format, arguments ) ;
		st_printf( buffer ) ;
		va_end( arguments ) ;
		st_printf( "\r\n" ) ;
		result = 0 ;
	}
	test_number++ ;
	return result ;
}

//////////////////////////////////////////////////////////////////////////
// Begin unit tests //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// do the unit tests
int test()
{
	int passcount = 0 ;
	int failcount = 0 ;
	
  // Example tests	
	st_printf( "\r\nTests for example_1 and example_2...................\r\n" ) ;
	// Test 1
	uint32_t result = example_1( 5 ) ;
	assert( result == 6,
		"Expected the value 6 but got %d", result )
		? passcount++ : failcount++ ;

	// Test 2
	char *input_string = "TheTest" ;
	char *updated_pointer = example_2( input_string ) ;
	assert( *updated_pointer == *(input_string + 1),
		"Expected the %c but got %c", *( input_string + 1 ), *updated_pointer )
		? passcount++ : failcount++ ;

	st_printf( "\r\nTests for test_for_bit_value........................\r\n" ) ;
	// Test 3
	uint8_t bit_test = test_for_bit_value( 4, 0 ) ;
	assert( bit_test == 0,
		"Expected 0 value for bit 0 but got %d", bit_test )
		? passcount++ : failcount++ ;

	// Test 4
	bit_test = test_for_bit_value( 4, 1 ) ;
	assert( bit_test == 0,
		"Expected 0 value for bit 1 but got %d", bit_test )
		? passcount++ : failcount++ ;

	// Test 5
	bit_test = test_for_bit_value( 4, 2 ) ;
	assert( bit_test == 1,
		"Expected 1 value for bit 2 but got %d", bit_test )
		? passcount++ : failcount++ ;

	// Test 6
	bit_test = test_for_bit_value( 4, 3 ) ;
	assert( bit_test == 0,
		"Expected 0 value for bit 3 but got %d", bit_test )
		? passcount++ : failcount++ ;

	st_printf( "\r\nTests for swap_case_in_string........................\r\n" ) ;
	// Test 7
	char output_string[20] ;
	char *input = "s" ;
	char *expected = "S" ;
	swap_case_in_string( input, output_string ) ;
	assert( strcmp( expected, output_string ) == 0,
		"Expected %s but got %s", expected, output_string )
		? passcount++ : failcount++ ;

	// Test 8
	input = "12abCD" ;
	expected = "12ABcd" ;
	swap_case_in_string( input, output_string ) ;
	assert( strcmp( expected, output_string ) == 0,
		"Expected %s but got %s", expected, output_string )
		? passcount++ : failcount++ ;

	// Test 9
	// Add a test for an empty input string
	input = "";
	expected = "";
	swap_case_in_string(input, output_string);
	assert(strcmp(expected, output_string) == 0,
			"Expected %s but got %s", expected, output_string)
			? passcount ++ : failcount++ ;

	// Test 10
	// Add a test for an input string containing "123456"
	input = "123456";
	expected = "123456";
	swap_case_in_string(input, output_string);
	assert(strcmp(expected, output_string) == 0,
			"Expected %s but got %s", expected, output_string)
			? passcount ++ : failcount++ ;
	
		
	st_printf( "\r\nSummary of unit tests:\r\n%d tests passed\r\n%d tests failed\r\n\n", passcount, failcount ) ;
	
	return failcount ;
}

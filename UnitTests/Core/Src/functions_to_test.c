// functions_to_test.c
// Larry Kiser Created for the STM32 bare metal environment Feb. 24, 2019

#include <ctype.h>
#include "functions_to_test.h"


// Add the functions to be tested here and in the corresponding header file.

// Example function to test -- just adds one to received value.
uint32_t example_1( uint32_t input_value )
{
	return ++input_value ;		// add one to input value and return that value
}

// Example function to test -- returns the wrong string
char *example_2( char *input_string )
{
	char* return_character;
	return_character = &input_string[1];
	return return_character;		// This line is wrong. Fix it so it returns pointer to 2nd character in the string
}

// test_for_bit_value
// This function returns 1 if the bit_position in byte_value is true (set) or returns 0 if false.
// Note that bit_position values range from 0 through 7 with 0 as the least significant bit.
uint8_t test_for_bit_value( uint8_t byte_value, uint8_t bit_position )
{
	if(byte_value & (1<<bit_position)){ //if value of bit_position is 1, then its set
		return 1; //so return 1
	}else{
		return 0; //otherwise return 0
	}
	//return byte_value & 1<<bit_position;
}

// This function copies every character from the input string to the
// output string but changes every letter to the opposite case (e.g. 'c' becomes 'C', 'Z' becomes 'z').
// Characters that are not letters are unaltered. Be sure to copy the end of string marker!
// You may assume that the output string has sufficient space to store the result and that both pointers
// are valid pointers.
// You are allowed to use the isupper, islower, toupper, and tolower functions.
void swap_case_in_string( char *input_string, char *output_string )
{
//	char *temp_char;
//	int size = strlen(input_string);
//	for(int i = 0; i < size; i++){
//		if(isupper(input_string[i])){
//			temp_char = tolower(input_string[i]);
//		}else if(islower(input_string[i])){
//			temp_char = toupper(input_string[i]);
//		}
//		strcat(output_string, temp_char);
//	}
	char temp_string[20];
	int i = 0;
	while(input_string[i] != '\0'){
	    if(isupper(input_string[i])){
	    	temp_string[i] = tolower(input_string[i]);;
	    }
	    else if(islower(input_string[i])){
	        temp_string[i] = toupper(input_string[i]);;
	    }
	    else{
	    	temp_string[i] = input_string[i];
	    }
	    i++;
	}
	temp_string[i] = '\0';
	strcpy( output_string, temp_string) ;		// bogus code to force unit tests to fail
}

/* Name: iaps.c
 * Author: Will St. Onge
 * Description: Computes an increasing sequence of prime numbers between the starting and ending number inputted by the user using Intel x86 assembly. The algorithm for find the next number in the sequence and print it out is written in x86 assembly. It starts at the first input number and checks if that is prime. If it is prime, it will output that number to console and add that to the accumulator and current equal to it. If it is not prime, it will increment the current number by 1. Once the end number is reached, the program will stop.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	// Return value for isPrime.
	int ret;
	// Range of numbers acceptable.
	int start, end;
	// Current number and accumulator for increasing additive sequence.
	int current, acc = 0;
	// Format for printf.
	char* str = "%d ";

	// Get user inputs
	printf("Insert a starting number: ");
	scanf("%d", &start);
	printf("Insert a maximum number: ");
	scanf("%d", &end);

	__asm
	{
		mov eax, start			// Initialize the current number to the starting number.
		mov current, eax
		cmp eax, end			// Test if start is greater than end, if it is then the inputs are invalid and we need to exit the program.
		jg breakout
	top:						
		mov eax, current		// Move the current number into eax so we can do comparisons and arithmeic.
	inner:						
		cmp eax, end			// If the current number is greater than or equal to the end number, exit the program since we are outside of the range of the sequence.
		jge breakout
		jmp isPrime				// Jump to the isPrime routine to test primality of current.
	returnpoint:				
		cmp ret, 1				// If the return value from the isPrime routine is a 1, the number is prime so print out the number and do arithmetic on current and acc.
		je condition
		inc current				// Number is not prime, increment current and see if that number is prime.
		jmp inner
	condition:					
		push current			// Pushes format and data onto the stack for printf call.
		push str
		call printf				// Call the printf function to print out the next number in the sequence.
		pop ecx					// Pop the format and number of the top of the stack so nothing is messed up.
		pop ecx
		mov eax, current		// Move current into the eax register so it can be added to acc.
		add acc, eax			// Increment acc by current so we can keep the sequence increasingly additive.
		mov eax, acc			// Set current equal to acc + 1 so we know where to start in the next iteration.
		inc eax
		mov current, eax
		jmp top					// Loop back up to the top of the program so we can continue the sequence.
	isPrime:					// isPrime routine for finding if a number is prime or not.
		mov ebx, 2				// Initialize the divisor to 2
	primeLoop:
		mov eax, current		// Confirm eax is still current since we're using the div operator.
		cmp ebx, eax			// Make sure the current divisor is less than the number so we dont divide the number by itself. If it is, go back to the main part of the program.
		jge returnpoint
		mov edx, 0				// Make sure edx is 0 so we don't get quotient/remainder inaccuracy.
		mov ret, 0				// Reset ret to 0 so the routine doesn't return 1 when it shouldn't.
		div ebx					// Divide eax by ebx. This puts the quotient into eax and the remainder in edx.
		cmp edx, 0				// If the remainder (edx) is 0, then current is not prime. Escape from the isPrime logic and go back to the main program.
		je returnpoint
		mov edx, 1				// Set ret to 1, signaling that eax is prime.
		mov ret, edx
		inc ebx					// Increment the divisor so we dont divide by the same number twice.
		jmp primeLoop			// Jump back up to the loop start so we can test the next divisor.
	breakout:
	}
}
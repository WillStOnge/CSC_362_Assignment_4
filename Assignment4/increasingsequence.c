/*	
	Name: IPS.c
	
	Author: Will St. Onge

	Description: Computes an increasing sequence of prime numbers between the starting and ending number inputted by the user. The algorithm for find the next number in the sequence and print it out is written in x86 assembly. It starts at the first input number and checks if that is prime. If it is prime, it will output that number to console and add that to the accumulator and current equal to it. If it is not prime, it will increment the current number by 1. Once the end number is reached, the program will stop.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	// Return value for isPrime (boolean)
	int ret;
	// Range of numbers acceptable (sser input)
	int start, end;
	// Current number and accumulator for increasing sequence
	int current, acc = 0;
	// Format for printf
	char* str = "%d ";

	// Get user inputs
	printf("Insert a starting number: ");
	scanf("%d", &start);
	printf("Insert a maximum number: ");
	scanf("%d", &end);

	// Check that end is greater than start
	if (end <= start)
	{
		printf("\nStarting number must be less than the maximum number");
		return 1;
	}

	// Set the current number to start
	current = start;

	__asm
	{
	top:						; Top of the program (main loop).

		mov eax, current		; Move the current number into eax.
		
	inner:						; Inner loop of the program.
		
		cmp eax, end			; If the current number is >= the end number, exit the program.
		jge breakout

		jmp isPrime				; Jump to the isPrime routine to test primality of current.

	returnpoint:				; Return point for the isPrime code.

		cmp ret, 1				; If the return value is a 0, the number is prime so continue to the if logic.
		je condition

		inc current				; Number is not a prime, increment current and see if that number is prime.
		jmp inner

	condition:					; If the number is prime, this get ran.

		push current			; Pushes format and data onto the stack.
		push str

		call printf				; Call the printf function.

		pop ecx					; Cleanup the stack.
		pop ecx

		mov eax, current		; Move current into the eax register so it can be added to acc.

		add acc, eax			; Increment acc by current.

		mov ebx, acc			; Set current equal to acc + 1.
		inc ebx
		mov current, ebx

		jmp top					; Loop back up to the top of the program.
		
	isPrime:					; Check if a number is prime.

		mov ebx, 2				; Initialize the divisor to 2

	primeLoop:					; loop for the isPrime logic

		mov eax, current		; Confirm eax is still current.

		cmp ebx, eax			; Make sure the current 'index' is less than the number.
		jge returnpoint

		mov edx, 0				; Make sure edx is 0 so we don't get modulo inaccuracy.
		mov ret, 0				; Reset ret to 0 so the routine doesn't return 1 when it shouldn't.

		div ebx					; Divide eax by ebx. This puts the result in eax and the remainder in edx.

		cmp edx, 0				; If the remainder is 0, then current is not prime. Escape from the isPrime logic and go back to the main program.
		je returnpoint

		mov edx, 1				; Set ret to 1, signaling that eax is prime.
		mov ret, edx

		inc ebx					; Increment the divisor.

		jmp primeLoop			; Continue the loop.

	breakout:					; Escape point for the program.
		nop						; No operation.
	}
}
// Name: IncreasingPrimeSequence.c
// Author: Will St. Onge
// Description: Computes an increasing sequence of prime numbers between the starting and ending number inputted by the user. The algorithm for find the next number in the sequence is written in x86 asm.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int isPrime(int); // Checks if a number is prime


int main()
{
	int start, end, current, acc = 0;
	char* str = "%d ";

	// Get user inputs
	printf("Insert a starting number: ");
	scanf("%d", &start);
	printf("Insert a maximum number: ");
	scanf("%d", &end);

	// Check that end is greater than start
	if (!(end > start))
	{
		printf("\nStarting number must be less than the maximum number");
		return 1;
	}

	current = start;

	/*
	while (1)
	{
		while (!isPrime(current))		jmp isPrime - cmp edx, 1 - je if statement - jmp inner
			current++;					inc current
		if (current < end)				mov ecx, current - cmp ecx, end - jge breakout
		{
			printf("%d ", current);		push current - call prinf - pop eax
			acc += current;				add acc, eax
			current = acc + 1;			mov eax, acc - inc eax - mov current, eax
		}
		else 
			break;
	}
	*/

	__asm // main sub-routine
	{
	loop1:					; Main loop of the sub-routine

		mov eax, current
		mov edx, 0
		mov ebx, 2

	returnpoint:			; Point to comeback from isPrime

		jmp	isPrime			; Check if current is prime if so, jmp to the if statement below
		cmp edx, 0
		je conditional
		jmp loop1

		inc eax
		jmp loop1

	conditional:			; If statement of the equivalent C code.

		cmp eax, end		; Breakout of the loop if current >= end
		jge breakout

		push current		; Push arguments onto stack, call printf, then clean up the stack
		push str
		call printf
		pop ebx
		pop ebx

		add acc, eax		; Increment acc by current
		
		mov eax, acc		; current = acc + 1
		inc eax				
		mov current, eax

		jmp loop1			; jump back up to the top
 
	isPrime:				; isPrime() sub-routine (in: eax, out: edx)
		mov eax, current
		div ebx				; divide eax by ebx, remainder goes into edx

		cmp edx, 0			; if remainder is 0 or current > num - 1, then number is not prime
		jmp returnpoint
		inc ebx
		cmp ebx, eax
		jge returnpoint

		cmp eax, end		; if current >= end, breakout of the program
		jge breakout

		jmp isPrime			; loop back up
	}

breakout:
	return;
}
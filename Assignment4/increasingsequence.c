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

	__asm
	{
	loops:					; Main loop of the sub-routine

							; call isPrime(eax) and cmp the returned value to 0, then je condition
		mov eax, current
		inc eax
		jmp loops

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

		jmp loops			; jump back up to the top
	}

breakout:
	return;
}

int isPrime(int num)
{
	if (num < 4 || !(num % 2))
		return 0;
	for (int i = 3; i < num - 1; i++)
		if (!(num % i))
			return 0;
	return 1;
}
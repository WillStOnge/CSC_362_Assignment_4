// Name: IncreasingPrimeSequence.c
// Author: Will St. Onge
// Description: Computes an increasing sequence of prime numbers between the starting and ending number inputted by the user. The algorithm for find the next number in the sequence is written in x86 asm.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void isPrime(int); // Checks if a number is prime
int ret; // Return variable for isPrime

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
	top:						; Top of the program (main loop)

		mov eax, current		; Move the current number into eax

	inner:						; Inner loop of the program
		
		cmp eax, end			; If the current number is >= the end number, exit the program
		jge breakout

		push current			; Push the current number onto the stack, call isPrime, then clean the stack
		call isPrime
		pop edx

		cmp ret, 0				; If the return value is a 0, the number is prime so continue to the if logic
		je condition

		inc current				; Number is not a prime, increment current and see if that is prime
		jmp inner

	condition:
		

	breakout:
		nop
	}
	return 0;
}

void isPrime(int num)
{
	if (num <= 3 || !(num % 2))
	{
		ret = 0;
		return;
	}
	for (int i = 2; i < num; i++)
		if (!(num % i))
		{
			ret = 0;
			return;
		}
	ret = 1;
}
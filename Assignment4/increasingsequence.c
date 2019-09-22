// Name: IncreasingPrimeSequence.c
// Author: Will St. Onge
// Description: Computes an increasing sequence of prime numbers between the starting and ending number inputted by the user. The algorithm for find the next number in the sequence is written in x86 asm.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int isPrime(int); // Checks if a number is prime

int main()
{
	int start, end, current, acc = 0;

	// Get user inputs
	printf("Insert a starting number: ");
	scanf("%d", &start);
	printf("Insert a maximum number: ");
	scanf("%d", &end);
	current = start;

	// Check that end is greater than start
	if (!(end > start))
	{
		printf("\nStarting number must be less than the maximum number");
		return 1;
	}

	/*
	// Start asm
	while (1)
	{
		while (!isPrime(current)) // cmp [rbp-4], 0 - je breakout
			current++; // add current, 1
		if (current < end) // cmp current, end - jge breakout
		{
			acc += current; // add acc, current
			current = acc + 1; // mov current, acc - add acc, 1
			printf("%d ", current); // jmp print
		}
		else 
			break; // jmp breakout
	}
	*/

	__asm {
	innerloop: 
		mov eax, DWORD PTR [current]
		call isPrime
		cmp ecx, 1
		je condition
		add current, 1
		jmp innerloop
	condition: 
		mov ebx, end
		cmp current, ebx
		jge breakout
		mov eax, DWORD PTR[current]
		add acc, eax
		mov eax, DWORD PTR[acc]
		add eax, 1
		mov current, eax
		jmp print
		jmp innerloop
	}

	goto breakout;
print: printf("%d ", current);
breakout:
	return 1;
}

int isPrime()
{
	int num, ret = 1;

	__asm {
		mov DWORD PTR[num],	eax
	}

	if (num < 4 || !(num % 2))
		ret = 0;
	for (int i = 3; i < num - 1; i++)
		if (!(num % i))
			ret = 0;

	__asm {
		mov ecx, ret
	}
}
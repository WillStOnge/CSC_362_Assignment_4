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

	// Check that end is greater than start
	if (!(end > start))
	{
		printf("\nStarting number must be less than the maximum number");
		return 1;
	}

	current = start;

	// Start asm
	while (1)
	{
		while (!isPrime(current))
			current++;
		if (current < end)
		{
			printf("%d ", current);
			acc += current;
			current = acc + 1;
		}
		else 
			break;
	}
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
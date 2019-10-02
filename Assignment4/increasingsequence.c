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
		while (!isPrime(current))		//jmp isPrime - cmp edx, 1 - je if statement - jmp inner
			current++;					//inc current
		if (current < end)				//mov ecx, current - cmp ecx, end - jge breakout
		{
			printf("%d ", current);		//push current - call prinf - pop eax
			acc += current;				//add acc, eax
			current = acc + 1;			//mov eax, acc - inc eax - mov current, eax
		}
		else 
			break;
	}
	*/

	// eax = current
	// ebx = whatever
	// ecx = whatever
	// edx = remainder
	// Use ax, bx, cx, dx for isPrime

	__asm
	{
	top:						; Top of the program (main loop).

		mov eax, current		; Move the current number into eax.
		
	inner:						; Inner loop of the program.
		
		cmp eax, end			; If the current number is >= the end number, exit the program.
		jge breakout

		push current			; Push the current number onto the stack, call isPrime, then clean the stack.
		call isPrime
		pop edx

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

		add acc, eax			; Increment acc by current.

		mov ebx, acc			; Set current equal to the number after the acc.
		inc ebx
		mov current, ebx

		jmp top					; Loop back up to the top of the program.
		
	isPrime:					; Check if a number is prime.

		mov ebx, 2
		mov ret, 1

	primeLoop:						; loop for the isPrime logic

		mov eax, current		; Confirm eax is still current.

		cmp ebx, eax			; Make sure the current 'index' is less than the number.
		jge returnpoint

		div ebx					; Divide eax by ebx. This puts the result in eax and the remainder in edx.

		cmp edx, 0				; If the remainder is 0, then current is not prime. Escape from the isPrime logic and go back to the main program.
		jne returnpoint

		mov edx, 1				; Set ret to 1 signaling that eax is prime.
		mov ret, edx

		jmp primeLoop			; Continue the loop

	breakout:
		nop
	}

	return 0;
}

void isPrime(int num)
{
	for (int i = 2; i < num; i++)
		if (!(num % i))
		{
			ret = 0;
			return;
		}
	ret = 1;
}
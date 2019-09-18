#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	int start, end;
	printf("Insert a starting number: ");
	scanf("%d", &start);
	printf("Insert a maximum number: ");
	scanf("%d", &end);

	if (!(end > start))
	{
		printf("\nStarting number must be less than the maximum number");
		return 1;
	}



	/*
	__asm
	{

	}
	*/
}
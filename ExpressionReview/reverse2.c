/*
reverse2.c
by Deepti Ramani
12/9/2019
program that reverses a given 2-digit number

gcc -Wall -Wextra -Werror -ansi -pedantic -O reverse2.c -o reverse2.exe
*/

/* printf, scanf */
#include <stdio.h>

int main(void)
{
	int input;
	printf("Please enter a 2-digit number: ");
	scanf(" %i", &input);
	while(input < 10 || input > 99)
	{
		printf("Please enter a 2-digit number: ");
		scanf(" %i", &input);
	}
	printf("Your reversed number is %i%i\n", input % 10, input / 10);
	return 0;
}
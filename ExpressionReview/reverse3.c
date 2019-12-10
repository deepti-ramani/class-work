/*
reverse3.c
by Deepti Ramani
12/9/2019
program that reverses a given 3-digit number

gcc -Wall -Wextra -Werror -ansi -pedantic -O reverse3.c -o reverse3.exe
*/

/* printf, scanf */
#include <stdio.h>

int main(void)
{
	int input;
	printf("Please enter a 3-digit number: ");
	scanf(" %i", &input);
	while(input < 100 || input > 999)
	{
		printf("Please enter a 3-digit number: ");
		scanf(" %i", &input);
	}
	printf("Your reversed number is %i%i%i\n", input % 10, input % 100 / 10, input / 100);
	return 0;
}
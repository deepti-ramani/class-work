/*
numberguess.c
by Deepti Ramani
12/9/2019
program that runs a number guessing game

gcc -Wall -Wextra -Werror -ansi -pedantic -O numberguess.c -o numberguess.exe
*/

/* printf, scanf */
#include <stdio.h>

/* rand, srand */
#include <stdlib.h> 

int main(void)
{
	int random = rand() % 10 + 1;
	int guess = 0;
	int count = 1;
	printf("Guess a number between 1 and 10: ");
	scanf(" %i", &guess);
	while(guess != random)
	{
		if(guess > random)
		{
			printf("Too high. Guess again: ");
		}
		else if(guess < random)
		{
			printf("Too low. Guess again: ");
		}
		scanf(" %i", &guess);
		count++;
	}
	printf("You got it in %i guesses!\n", count);
	return 0;
}
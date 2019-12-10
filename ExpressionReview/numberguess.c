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

/* time */
#include <time.h>

int main(void)
{
	int randomNumber = 0;
	int guess = 0;
	int countGuesses = 1;
	
	srand(time(0));
	randomNumber = rand() % 10 + 1;
	
	printf("Guess a number between 1 and 10: ");
	scanf(" %i", &guess);
	
	while(guess != randomNumber)
	{
		if(guess > randomNumber)
		{
			printf("Too high. Guess again: ");
		}
		else if(guess < randomNumber)
		{
			printf("Too low. Guess again: ");
		}
		scanf(" %i", &guess);
		countGuesses++;
	}
	
	printf("You got it in %i guesses!\n", countGuesses);
	
	return 0;
}
/*
ZombieDice.c
by Deepti Ramani
Implements the ZombieDice game in C
11/14/2019

gcc -Wall -Wextra -Werror -ansi -pedantic -O ZombieDice.c -o zombiedice.exe
*/

/* printf, scanf */
#include <stdio.h>
/* rand, srand */
#include <stdlib.h> 

#define NUMBER_OF_PLAYERS 3
#define RED 2
#define YELLOW 1
#define GREEN 0

/* return player score at the end of their turn*/
int PlayerTurn(int selected_dice[], int dice_pool[], int *pool_size);

/* check for win condition at the end of each player's turn */
int CheckWinner(int player_scores[]);

/* pick next dice for the next roll of the player */
void SelectDice(int selected_dice[], int dice_pool[], int *pool_size);

/* main */
int main(void)
{
	int i;
	char input;
	
	/* create an array of dice to draw from */
	int pool_size = 13;
	int dice_pool[] = { GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED };
	
	/* create an array for the selected dice */
	int selected_dice[] = { -1, -1, -1 };
	
	/* create an array to store scores of all players */
	int player_scores[NUMBER_OF_PLAYERS] = { 0 };
	
	int winner = -1;	/* keeps track of if there's a winner */
	int player = 0;		/* keeps track of player turns */
	
	printf("Welcome to the game of Zombie Dice!\n");
	
	/* game loop */
	do
	{	
		/* player can skip their turn if they want */
		printf("\n\nPlayer %i, ready to play(y or n)? ", (player + 1));	
		scanf(" %c", &input);
		while(getchar() != '\n');
		
		if(input == 'y')
		{
			player_scores[player] += PlayerTurn(selected_dice, dice_pool, &pool_size);
			printf("Player %i's score at the end of the turn: %i\n", (player + 1), player_scores[player]);
		}
		
		/* check for winner once all players have played an equal number of times */
		if(player == (NUMBER_OF_PLAYERS - 1))
		{
			winner = CheckWinner(player_scores);
		}
		player++;
		player %= NUMBER_OF_PLAYERS;
	} 
	while(winner == -1);
	
	/* when winner != -1, the loop ends and the final scores are printed */
	printf("\nThe winner is Player %i!\n\n\n", winner + 1);
	printf("Final Scores: \n");
	for(i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		printf("Player %i: %i\n", i + 1, player_scores[i]);
	}
	
	return 0;
}

/* return player score at the end of their turn*/
int PlayerTurn(int selected_dice[], int dice_pool[], int *pool_size)
{
	char input;
	int number_of_brains = 0;
	int number_of_shots = 0;
	int number_of_runners = 0;
	int i;
	do
	{	
		/* pick 3 dice from pool and determine their colors in selected_dice*/
		SelectDice(selected_dice, dice_pool, pool_size);
		
		/* roll each dice and store what value it is in brains/shots/runners */
		printf("\nYou rolled: ");
		for(i = 0; i < 3; i++)
		{
			int random = rand() % 6 + 1;
			
			/* if brain or shot, set selected_dice value to -1 to prepare for re-roll & increment counter */
			/* if runner, leave the value in the array & increment counter */
			switch(selected_dice[i])
			{
				case GREEN:
				{
					
					printf("Green ");
					if(random <= 3)
					{
						printf("(brain)  ");
						number_of_brains++;
						selected_dice[i] = -1;
					}
					else if(random == 4)
					{
						printf("(shot)  ");
						number_of_shots++;
						selected_dice[i] = -1;
					}
					else
					{
						printf("(runner)  ");
						number_of_runners++;
					}
					break;
				}
				case YELLOW:
				{
					printf("Yellow ");
					if(random <= 2)
					{
						printf("(brain)  ");
						number_of_brains++;
						selected_dice[i] = -1;
					}
					else if(random <= 4)
					{
						printf("(shot)  ");
						number_of_shots++;
						selected_dice[i] = -1;
					}
					else
					{
						printf("(runner)  ");
						number_of_runners++;
					}
					break;
				}
				case RED:
				{
					printf("Red ");
					if(random == 1)
					{
						printf("(brain)  ");
						number_of_brains++;
						selected_dice[i] = -1;
					}
					else if(random <= 4)
					{
						printf("(shot)  ");
						number_of_shots++;
						selected_dice[i] = -1;
					}
					else
					{
						printf("(runner)  ");
						number_of_runners++;
					}
					break;
				}
			}
		}
		printf("\nTotals for this turn: %i brain(s) | %i shot(s)\n", number_of_brains, number_of_shots);
		
		/* check if there are three+ shots for forced end of turn */
		if(number_of_shots >= 3)
		{
			printf("You have been shot three or more times. Your turn is over and you lose points earned this round.\n");
			/* end turn with 0 points */
			return 0;
		}
		
		/* print dice pool at beginning of each roll*/
		printf("Dice Pool: ");
		for(i = 0; i < *pool_size; i++)
		{
			switch(dice_pool[i])
			{
				case 0:
				{
					printf("G  ");
					break;
				}
				case 1: 
				{
					printf("Y  ");
					break;
				}
				case 2:
				{
					printf("R  ");
				}
			}
		}
		printf("\n");
		
		/* ask if the player wants to continue or stop */
		printf("Continue (y or n)? ");
		scanf(" %c", &input);
		while(getchar() != '\n');		
		
	} 
	while(input == 'y');
	
	/* returns score when player turn ends */
	return number_of_brains;
}

/* check for win condition at the end of each player's turn */
int CheckWinner(int player_scores[])
{
	/* i is index of player */
	int i;
	for(i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if(player_scores[i] >= 13)
		{
			return i;
		}
	}
	/* -1 = no winner */
	return -1;
}

/* pick next dice for the player */
void SelectDice(int selected_dice[], int dice_pool[], int *pool_size)
{
	int i;
	int random;
	
	/* picks dice from the intial pool of 13 dice */
	for(i = 0; i < 3; i++)
	{
		random = rand() % 13;
		/* if it isn't a runner */
		if(selected_dice[i] == -1)
		{
			/* store the color of the selected dice (GREEN, YELLOW, RED) */
			selected_dice[i] = dice_pool[random];
			
			/* change pool size since someone picked a dice */
			dice_pool[random] = dice_pool[*pool_size - 1];
			dice_pool[*pool_size - 1] = selected_dice[i];
			*pool_size = *pool_size - 1;
			
			/* add dice back into pool */
			if(*pool_size <= 0)
			{
				*pool_size = 13;
			}
		}
	}
}

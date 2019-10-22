/***********************************
TicTacToe.c
10/1/17
Programmed By: The Masked Programmer and Deepti Ramani 
Brief: Tic Tac Toe game with some missing components to be fixed.
gcc -Wall -Wextra -ansi -pedantic -O -o TicTacToe TicTacToe.c
***********************************/
/*printf scanf*/
#include <stdio.h>

/*function prototypes*/
/*function will need to look at the grid and determine if there is a winner or if it is a tie*/
int CheckGrid(int Grid[][3]);
/*print out the board for the players*/
void printBoard(int Grid[][3]);

/*contains main game loop and player input runs other functions*/
int main(void)
{
	/*2D array for our grid, 3x3*/
	int Grid[3][3] = {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
	/* 0 is for O 1 is for X*/
	int playerTurn = 1;
	int input;
	int gameState = CheckGrid(Grid);
	printf("Welcome to Tic Tac Toe!\nTake turns with another player chosing places.\n");
	
	while(gameState == -1)
	{
		/*display board with numbers*/
		printBoard(Grid);
		if(playerTurn == 1)
		{
			printf("Player X's Turn, select your position:\n");
		}
		else
		{
			printf("Player O's Turn, select your position:\n");
		}
		/*Get input from the current player*/
		while(1)
		{
			scanf(" %i", &input);
			while(getchar() != '\n');
			if(input >= 0 && input < 9 && Grid[input/3][input%3] == -1)
			{
				/*legal input found*/
				Grid[input/3][input%3] = playerTurn;
				break;
			}
			printf("Invalid Input\n");
			
		}
		/*change playerturn*/
		if(playerTurn)
		{
			playerTurn = 0;
		}
		else
		{
			playerTurn = 1;
		}
		gameState = CheckGrid(Grid);
	}
	printBoard(Grid);
	/*determines winner*/
	switch(gameState)
	{
		case 0:
		printf("Player O Wins!\n");
		break;
		case 1:
		printf("Player X Wins!\n");
		break;
		case 2:
		printf("Tie!\n");
		break;
	}
	getchar();
	return 0;
}

/* function will need to look at the grid and determine if there is a winner or if it is a tie */
int CheckGrid(int Grid[][3])
{
	int continuePlaying = 2;
	int i, j;	/* i counts rows, j counts columns */
	
	/* HARD CODED SOLUTION FOR DIAGONALS: */
	if(Grid[0][0] == Grid[1][1] && Grid[1][1] == Grid[2][2])
	{
		return Grid[0][0];
	}
	if(Grid[2][0] == Grid[1][1] && Grid[1][1] == Grid[0][2])
	{
		return Grid[2][0];
	}

	/* loop through rows */
	for(i = 0; i < 3; i++)
	{
		/* checks if there is a winning row */
		if(Grid[i][0] == Grid[i][1] && Grid[i][1] == Grid[i][2])
		{
			/* returns winning number */
			return Grid[i][0];
		}
		
		/* loop through columns */
		for(j = 0; j < 3; j++)
		{
			/* checks if there is a winning column */
			if(Grid[0][j] == Grid[1][j] && Grid[1][j] == Grid[2][j])
			{
				/* returns winning number */
				return Grid[0][j];
			}
			
			/* checks if there are any empty spaces left (if there aren't, it's a tie) */
			if(Grid[i][j] == -1)
			{
				continuePlaying = -1;
			}
		}
	}
	
	/*return 2 for tie, -1 for continue playing*/
	return continuePlaying;
}
/*print out the board for the players*/
void printBoard(int Grid[][3])
{
	int i,j;
	for(i = 0; i <3; i++)
	{
		printf("|");
		for(j = 0 ; j < 3 ; j++)
		{
			switch(Grid[i][j])
			{
				case -1:
				printf(" %i |", i * 3 + j );
				break;
				case 0:
				printf(" O |");
				break;
				case 1:
				printf(" X |");
				break;
			}
		}
		printf("\n\n");
	}
	return;
}


/* check diagonals - use hard coded for now */
int loopAttempt(int Grid[][3])
{
	int i;
	if(Grid[1][1] != -1)
	{
		/* check the middle of the grid because both diagonals use it */
		int temp = Grid[1][1];
		printf("temp is %i.\n", temp);
		
		/* check the other values of the diagonals */
		for(i = 0; i < 3; i++)
		{
			/* check first diagonal */
			if(Grid[i][i] == temp)
			{
				continue;
			}
			else
			{
				break;
			}
			
			/* only do this when first if is failed... 2 for loops? */
			if(Grid[i][2-i] == temp)
			{
				continue;
			}
			else
			{
				break;
			}
			
			/* if it gets to this point, one of the diagonals is three-in-a-row */
			if(i == 2)
			{
				return Grid[1][1];
			}
		}
	}
	return -1;
}
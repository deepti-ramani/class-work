/* srand, rand */
#include <stdlib.h>

/* time */
#include <time.h>

/* printf */
#include <stdio.h>


int RollDie(int sides)
{
	unsigned seconds = time(0);
	srand(seconds);
	/*printf("Seconds since 01 Jan 1970: %i\n", seconds);*/
	return rand() % sides + 1;
}

/* entry point of our program */
int main(void)
{
	printf("%i\n", RollDie(6));
	return 0;
}
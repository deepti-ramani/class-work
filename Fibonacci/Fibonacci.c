/*
Fibonacci.c
by Deepti Ramani
Last Edited: 09/23/2019
Description: A program that will print a specified number of terms in the fibonacci sequence
gcc -Wall -Wextra -Werror -ansi -pedantic -O Fibonacci.c -o fibonacci.exe
*/

/* printf */
#include <stdio.h>

int main(void)
{
	/* for keeping track of number of terms*/
	int numberOfTerms = 100;
	int count = 0;
	
	/* for calculating numbers in sequence */
	unsigned prev = 0;
	unsigned current = 1;
	unsigned temp = 0;
	
	printf("%u, ", prev);
	
	/* omit first and last terms from for loop -> numberOfTerms - 2 */
	for(count = 0; count < (numberOfTerms - 2); count++)
	{
		printf("%u, ", current);
		temp = current + prev;
		prev = current;
		current = temp;
	}
	
	/* the last number won't have the ", " */
	printf("%u\n", current);
	
	return 0;
}
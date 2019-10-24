/* 
SieveOfEratothenes.c
by Deepti Ramani
10/23/2019
Description

gcc -Wall -Wextra -Werror -ansi -pedantic -O main.c SieveOfEratothenes.c -o sieveOfEratothenes.exe
*/

/* printf */
#include <stdio.h>
/* sqrt */
#include <math.h>
/* TRUE, FALSE */
#include "SieveOfEratothenes.h"

/* param int a[] = array to sieve, param int size = array length - 1, return = void */
void sieve(int array[], int size)
{	
	/* indexes for looping */
	int i, j;
	
	/* initialize 0 and 1 as not primes */
	array[0] = FALSE;
	array[1] = FALSE;
	
	/* initialize all other values as primes */
	for(i = 2; i <= size; i++)
	{
		array[i] = TRUE;
	}
	
	/* go through each prime (starting from 2) */
	for(i = 2; i <= sqrt(size); i++)
	{
		/* check if index is prime */
		if(is_prime(i))
		{
			array[i] = TRUE;
			/* go through rest of the elements */
			for(j = i + 1; j <= size; j++)
			{
				/* set multiples of the index to FALSE */
				if(j % i == 0)
				{
					array[j] = FALSE;
				}
			}
		}
		else
		{
			array[i] = FALSE;
		}
	}
}

/* param int n = number to test, return = int (1 or 0) */
int is_prime(int n)
{
	/* index for looping */
	int i;
	
	/* divisible by 0 and 1 and itself still count as primes -> don't include in for loop */
	for(i = 2; i < n; i++)
	{
		/* if n is divisible by anything that isn't 0, 1, or itself, it isn't a prime */
		if(n % i == 0)
		{
			return FALSE;
		}
	}
	
	/* if it gets here, it is prime (no factors) */
	return TRUE;
}

/* param const int primes[] = array to search through, param int size = array length - 1, return = int (number of twin primes) */
int twin_primes(const int primes[], int size)
{
	/* index for looping */
	int i;
	
	/* keep track of number of twin primes */
	int count = 0;
	
	/* go through elements */
	for(i = 0; i <= size; i++)
	{
		/* if they are twin primes */
		if(primes[i] == 1 && primes[i + 2] == 1)
		{
			count++;
			printf("twin prime #%4i: %4i and %4i\n", count, i, i + 2);
		}
	}
	
	return count;
}

double brun_constant(const int primes[], int size)
{
	/* index for looping */
	int i;
	
	/* store brun's constant */
	double brun = 0;
	
	/* loop through all primes */
	for(i = 0; i <= size; i++)
	{
		/* if they are twin primes */
		if(primes[i] == 1 && primes[i + 2] == 1)
		{
			brun += ((1.0/i) + (1.0/(i + 2)));
		}
	}
	
	return brun;
}


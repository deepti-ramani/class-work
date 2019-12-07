/* gcc -Wall -Werror -Wextra -ansi -pedantic -O Euler.c -o euler.exe */

#include <stdio.h>

int isPrime(int n)
{
	int i; /* iterator */
	for(i = 2; i <= n / 2; i++)
	{
		if(n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

/* Problem 7: 10001st prime number (n = 10001) */
void nthPrime(int n)
{
	int countPrimes = 0;
	int nthPrime = 2;
	/* until n prime numbers are reached */
	while(countPrimes != n)
	{
		/* checks if number is prime */
		if(isPrime(nthPrime))
		{
			countPrimes++;
		}
		/* go to next number */
		nthPrime++;
	}
	
	/* undo final increment */
	nthPrime--;
	printf("%i is the %ist prime number.\n", nthPrime, n);
}

/* Problem 39: Integer right triangles */
void integerRightTriangles(void)
{
	int i, p = 12;
	int maxSolutions = 0;
	int currSolutions = 0;
	int a, b, c = 1;
	
	/* go through all perimeters */
	for(i = 12; i <= 1000; i++)
	{
		for(a = 1; a < i; a++)
		{
			for(b = 1; b < a; b++)
			{
				c = i - (a + b);
				if(a*a + b*b == c*c)
				{
					currSolutions++;
				}
			}
		}
		
		/* update max solutions */
		if(currSolutions > maxSolutions)
		{
			maxSolutions = currSolutions;
			p = i;
		}
		currSolutions = 0;
	}
	printf("The number of solutions is maximized at %i solutions, for a perimeter of %i.\n", maxSolutions, p);
}

/* Problem 50: Consecutive prime sums */
void consecutivePrimeSums()
{
	int prime = 2;
	int countPrimes = 0;
	int sum = 0;
	
	while(sum < 1000000)
	{
		if(isPrime(prime))
		{
			sum += prime;
			countPrimes++;
			/* double check end value */
			if(sum >= 1000000)
			{
				sum -= prime;
				countPrimes--;
				break;
			}
		}
		prime++;
	}
	
	printf("%i can be written as the sum of %i consecutive primes.\n", sum, countPrimes);
}

int main(void)
{
	nthPrime(10001);
	integerRightTriangles();
	consecutivePrimeSums();
	return 0;
}
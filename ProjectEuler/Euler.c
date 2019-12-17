/* gcc -Wall -Werror -Wextra -ansi -pedantic -O Euler.c -o euler.exe */

/* printf, scanf */
#include <stdio.h>

/* returns 1 if prime, 0 if not prime */
int isPrime(int n)
{
	int i;
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


/* Problem 16: Power digit sum */
void powerDigitSum(int power)
{
	int i;
	unsigned long num = 1;
	int sum = 0;
	for(i = 0; i < power; i++)
	{
		num *= 2;
	}
	printf("2^%i = %lu and the sum of its digits is ", power, num);
	while(num > 0)
	{
		printf("%lu ", num % 10);
		sum += num % 10;
		num /= 10;
		if(num > 0)
		{
			printf("+ ");
		}
	}
	printf("= %i.\n", sum);
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


/* Problem 48: Self powers */
void primePermutations()
{
	int i, j;
	unsigned long temp = 1;
	unsigned long sum = 0;
	
	for(i = 1; i < 1000; i++)
	{
		for (j = i; j > 0; j--)
		{
			temp *= i;
		}
		sum += temp;
		temp = 1;
	}
	printf("The last ten digits of the series 1^1 + 2^2 + 3^3 + ... + 1000^1000 are %lu.\n", sum);
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

/* Custom random generator using LCG */
int customRandom()
{
	static unsigned seed = 20;
	static int a = 104743;
	static int c = 116417;
	static int m = 163841;
	
	seed = (a * seed + c) % m;
	return seed;
}


/* test challenges */
int main(void)
{
	nthPrime(10001);
	powerDigitSum(15);
	integerRightTriangles();
	consecutivePrimeSums();
	primePermutations();
	return 0;
}
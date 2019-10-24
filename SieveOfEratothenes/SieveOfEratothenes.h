/*
SieveOfEratothenes.h
by Deepti Ramani
10/23/2019
Description
*/

#define FALSE 0
#define TRUE  1

void sieve(int array[], int size);
int is_prime(int n);
int twin_primes(const int primes[], int size);
double brun_constant(const int primes[], int size);
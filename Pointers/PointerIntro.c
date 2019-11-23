/*
PointerIntro.c
by Deepti Ramani
11/21/2019
Description: Intro to Pointers
gcc -Wall -Wextra -ansi -pedantic -O PointerIntro.c -o pointerintro.exe
*/

/* printf */
#include <stdio.h>

/* prototypes */
void test1(int* pa, int b);

/* Set up main function as normal */
int main(void)
{
	/* iterator */
	int i;
	
	/* Make an integer and set it as well as a pointer to an integer and set it to point at the first integer. */
	int a = 5;
	int b = 7;
	int c[3] = { 1, 2, 3 };
	
	/* Show proper way by getting the address of the first variable. &a is the address of a */
	int* pa = &a;
	
	/* Show that you can make a pointer to a pointer to an int, but that you cannot use the & operator twice in a row. Also that you cannot get the address of a literal value. */
	int** ppa = &pa;

	/* Make another int variable and show how we can access through the pointer. */
	b = a;
	b = *pa;
	b = **ppa;
	
	/* Also show dereferencing the first integer is bad. */
	b = *(&a);
	
	/* Print out many values to show what is happening. */
	printf("a    = %i\n", a);
	printf("pa   = %p | &a = %p\n", (void*)pa, (void*)&a);
	printf("ppa  = %p | &pa = %p\n", (void*)ppa, (void*)&pa);
	printf("&ppa = %p\n", (void*)&ppa);
	printf("\n");
	
	/* Demonstrate using a pointer as a function parameter (passed by reference) and how it is different than simply passing the normal int (passing by value). */
	printf("Before function: a = %i, b = %i\n", a, b);
	test1(&a, b);
	printf("After function: a = %i, b = %i\n", a, b);
	printf("\n");
	
	/* Make an integer array and show how pointers can be used with the array to print it out in a loop (iterate through the array with an iterator). */
	printf("c = { ");
	for(i = 0; i < 3; i++)
	{
		printf("%i at address %p ", *(c + i), (void*)(&c + i));
	}
	printf("}\n");
	
	/* Print out values with the array, and the pointer, too to show how they are relative to each other. */
	printf("c = { %i, %i, %i } | &c = %p\n", c[0], c[1], c[2], (void*)&c);
	printf("\n");
	
	return 0;
}

void test1(int* pa, int b)
{
	*pa = 7;
	b = 7;
	printf("Inside function: *pa = %i, b = %i\n", *pa, b);
}

/******************************************************************************
Filename: array.c
Author: Deepti
Date: 10/21/2019
Brief Description: A file containing 5 functions that perform various modifiers on arrays

gcc -O -Wall -Wextra -ansi -pedantic main1.c array.c -o array1

******************************************************************************/

/* 
	name: reverse_array
	description: reverses contents of array in place
	param: int a[] - array to be reversed
	param: int size - number of elements in array
	return: void - nothing is returned
*/
void reverse_array(int a[], int size)
{
	int temp;
	/* for half of the array */
	int i;
	for(i = 0; i < size / 2; i++)
	{
		/* set temp to the left value */
		temp = a[i];
		/* set the left value to the right value */
		a[i] = a[size - 1 - i];
		/* set the right value to temp */
		a[size - 1 - i] = temp;
	}
} 

/* 
	name: add_arrays
	description: add corresponding elements of two arrays
	param: const int a[] - first array to be used to find sum
	param: const int b[] - second array to be used to find sum
	param: int c[] - contains newly added array elements
	param: int size - number of elements in all three arrays
	return: void - nothing is returned
*/
void add_arrays(const int a[], const int b[], int c[], int size)
{
	/* for each element in array */
	int i;
	for(i = 0; i < size; i++)
	{
		/* assign sum of a and b to c */
		c[i] = a[i] + b[i];
		
	}
}

/* 
	name: scalar_multiply
	description: multiply each element in an array by a constant
	param: int a[] - array to be scaled
	param: int size - number of elements in array
	param: multiplier - what the elements are being multiplied by
	return: void - nothing is returned
*/
void scalar_multiply(int a[], int size, int multiplier)
{
	/* for each element in array */
	int i;
	for(i = 0; i < size; i++)
	{
		/* multiply element by multiplier */
		a[i] *= multiplier;
	}
}

/* 
	name: dot_product
	description: performs a dot product of two arrays
	param: const int a[] - first array to be used in dot product
	param: const int b[] - second array to be used in dot product
	param: int size - number of elements in both arrays
	return: int - return the integer value of the dot product
*/
int dot_product(const int a[], const int b[], int size)
{
	int dotProduct = 0;
	
	/* for each element in array */
	int i;
	for(i = 0; i < size; i++)
	{
		/* add the product of corresponding elements to dotProduct*/
		dotProduct += (a[i] * b[i]);
	}
	
	/* return dotProduct */
	return dotProduct;
}

/* 
	name: cross_product
	description: performs a cross product of two arrays and places them into a third array
	param: const int a[] - first array to be used in cross product
	param: const int b[] - second array to be used in cross product
	param: int size - number of elements in both arrays
	return: void - nothing is returned
*/
void cross_product(const int a[], const int b[], int c[])
{
	/* first element: c[0] = a[1]b[2] - a[2]b[1] */
	c[0] = (a[1] * b[2]) - (a[2] * b[1]);
	
	/* second element: c[1] = a[2]b[0] - a[0]b[2] */
	c[1] = (a[2] * b[0]) - (a[0] * b[2]);
	
	/* third element: c[2] = a[0]b[1] - a[1]b[0] */
	c[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

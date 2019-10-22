/*
pi.c
by Deepti Ramani
09/25/2019
Description: calculate pi using two algorithms (circle method & leibniz method)

gcc -Wall -Wextra -Werror -ansi -pedantic -O .\main.c .\pi.c -o pi.exe
*/

/*sqrt*/
#include <math.h>

/* Calculates PI using a quarter circle */
double circle_pi(int rectangles)
{
	/* constants */
	const double radius = 2.0;
	const double width = radius / rectangles;	/* same for all rectangles */
	
	/* changing */
	double xmultiplier = 0.5;	/* multiplier for width of triangle for finding height */
	double height;
	double pi = 0.0;

	int i;
	for(i = 0; i < rectangles; i++)
	{
		height = sqrt((radius * radius) - (xmultiplier * width * xmultiplier * width));
		pi += (width * height);
		xmultiplier += 1;
	}
	
	return pi;
}

/* Calculates PI using a series */
double leibniz_pi(int iterations)
{
	double pi = 0.0;
	double denominator = 1.0;
	
	int i;
	for(i = 0; i < iterations; i++)
	{
		/* even -> add next term in series */
		if( i % 2 == 0)
		{
			pi += (4.0 / denominator);
		}
		/* odd -> subtract next term in series*/
		else
		{
			pi -= (4.0 / denominator);
		}
		/* increment denominator by 2 */
		denominator += 2.0;
	}

	return pi;
}
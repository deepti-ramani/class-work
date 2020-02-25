/*****
fractions.c
By: Deepti Ramani
Last Edited: 2/21/2020
Description: contains functions to add, subtract, multiply, and reduce fractions
*****/

#include "fractions.h"
#include <stdio.h>

/* add two fractions */
struct FRACTION add_fractions(const struct FRACTION *a, const struct FRACTION *b)
{
	int scale;
	
	struct FRACTION added;
	added.numerator = a->numerator * b->denominator + b->numerator * a->denominator;
	added.denominator = a->denominator * b->denominator;

	scale = GCD(added.numerator, added.denominator);
	if(scale > 1)
	{
		added.numerator /= scale;
		added.denominator /= scale;
	}
	
	return added;
}

/* subtract fraction b from fraction a */
struct FRACTION subtract_fractions(const struct FRACTION *a, const struct FRACTION *b)
{
	struct FRACTION negativeB;
	negativeB.numerator = b->numerator * -1;
	negativeB.denominator = b->denominator;
	
	return add_fractions(a, &negativeB);
}

/* multiply two fractions */
struct FRACTION multiply_fractions(const struct FRACTION *a, const struct FRACTION *b)
{
	int scale;
	
	struct FRACTION multiplied;
	multiplied.numerator = a->numerator * b->numerator; 
	multiplied.denominator = a->denominator * b->denominator;
	
	scale = GCD(multiplied.numerator, multiplied.denominator);
	if(scale > 1)
	{
		multiplied.numerator /= scale;
		multiplied.denominator /= scale;
	}
	
	return multiplied;
}

/* reduce an improper fraction to a mixed number */
struct MIXED_FRACTION reduced_to_mixed(const struct FRACTION *fraction)
{
	struct MIXED_FRACTION mixed_fraction;
	
	if(fraction->denominator != 0)
	{
		mixed_fraction.whole_number =  (int)(fraction->numerator / fraction->denominator);
		mixed_fraction.proper_fraction.numerator = fraction->numerator - (fraction->denominator * mixed_fraction.whole_number);
		mixed_fraction.proper_fraction.denominator = fraction->denominator;
	}
	else
	{
		mixed_fraction.whole_number = 0;
		mixed_fraction.proper_fraction.numerator = 0;
		mixed_fraction.proper_fraction.denominator = 0;
	}
	
	
	return mixed_fraction;
}

/* get the greatest common denominator of two numbers */
int GCD(int a, int b)
{
	int r = 0;
	
	/* make sure a and b are positive */
	if(a < 0)
	{
		a *= -1;
	}
	if(b < 0)
	{
		b *= -1;
	}
	
	/* hardcoded cases if a or b or both are zero */
	if(!a && b)
	{
		return b;
	}
	if(!b && a)
	{
		return a;
	}
	if(!a && !b)
	{
		return 0;
	}
	
	/* GCD algorithm */
	r = a % b;
	while(r != 0)
	{
		a = b;
		b = r;
		r = a % b;
	}	
	return b;
}
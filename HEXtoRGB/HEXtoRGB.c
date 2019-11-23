/* 
	hex string will always have the following format: 
	#091FaA 
	where each digit can be from 0 to f in hex.
	You don't know if its caps or not 
	
	gcc -Wall -Wextra -ansi -pedantic -O HEXtoRGB.c -o HEXtoRGB.exe
*/

/* printf */
#include <stdio.h>

void HEXtoRGB(const char* hexString, int* R, int* G, int* B)
{
	int i = 0; /* iterator through hexString */
	int j = 0; /* iterator through rgbValues */
	int convertedHexString[6];
	int rgbValues[3];
	int temp;
	
	/* go through each value of the hexstring */
	for(i = 1; i < 7; i++)
	{
		/* get char to be converted to hex value using ASCII table */
		temp = *(hexString + i);
		
		/* 0 - 9 = integers */
		if(temp >= 48 && temp < 58)
		{
			temp -= 48;
		}
		/* 10 - 15 = uppercase A - F */
		else if (temp >= 65 && temp < 71)
		{
			temp -= 55;
		}
		/* 10 - 15 = lowercase a - f */
		else if (temp >= 97 && temp < 103)
		{
			temp -= 87;
		}
		/* else invalid input */
		else
		{
			printf("Invalid hex string.\n");
			return;
		}
		
		/* convertedHexString now holds the correct hex values of the char string */
		convertedHexString[i - 1] = temp;
	}
	
	/* iterate through three pairs of numbers to get dec values of rgb */
	for(i = 0; i < 6; i += 2)
	{
		/* calculate the dec value from hex values */
		temp = convertedHexString[i + 1]; 	/* add 1s place */
		temp += convertedHexString[i] * 16; /* add 16s place */
		
		/* store calculated values in rgbValues */
		rgbValues[j] = temp;
		j++;
	}
	
	/* set RGB values to R G and B */
	*R = rgbValues[0];
	*G = rgbValues[1];
	*B = rgbValues[2];
}


/* test in main */
int main(void)
{
	int R, G, B = 0;
	HEXtoRGB("#091FaA", &R, &G, &B);
	printf("HEX: #091FaA \nRGB: %i, %i, %i", R, G, B);
	return 0;
}
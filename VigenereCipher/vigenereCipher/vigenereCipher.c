/****************
vigenereCipher.c
By:
Date:
Brief:
gcc -O -Wall -Wextra -ansi -pedantic -o vcipher vigenereCipher.c main.c
****************/
#include "vigenereCipher.h"
#include <string.h>

void toLowercase(unsigned char *string)
{
	
}

void vigenere(unsigned char *string, unsigned char *key, enum CODE_METHOD method, int passes)
{
	int currPass = 0;
	int stringIndex = 0;
	int keyIndex = 0;
	int alphabetIndex = 0;
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	
	/* repeat the algorithm a set number of times */
	for(currPass = 0; currPass < passes; currPass++)
	{
		/* encode */
		if(method == ENCODE)
		{
			/* go through entire string */
			for(stringIndex = 0; stringIndex < (int)sizeof(string); stringIndex++)
			{
				/* skip if its a space */
				if(string[stringIndex] == ' ')
				{
					continue;
				}
				
				/* find the encoded letter and set it as the string*/
				alphabetIndex = ((int)string[stringIndex] % 97 + (int)key[keyIndex] % 97) % 26;
				string[stringIndex] = alphabet[alphabetIndex];

				/* update the current key letter */
				keyIndex++;
				
				/* make sure the index is within bounds */
				if(keyIndex >= (int)sizeof(key))
				{
					keyIndex = 0;
				}
			}
		}
		/* decode */
		else if(method == DECODE)
		{
			/* go through entire string */
			for(stringIndex = 0; stringIndex < (int)sizeof(string); stringIndex++)
			{
				/* skip if its a space */
				if(string[stringIndex] == ' ')
				{
					continue;
				}
				
				/* find the original letter */
			}
		}
	}
	
	return;
}


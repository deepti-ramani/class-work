/****************
vigenereCipher.c
By: Deepti Ramani
Date: 02/19/2020
Brief: Contains a function to encode and decode a given string with a provided key and number of passes
gcc -O -Wall -Wextra -ansi -pedantic -o vcipher vigenereCipher.c main.c
****************/
#include "vigenereCipher.h"
#include <string.h>

/* convert any uppercase letters to lowercase letters */
void toLowercase(char *string)
{
	int stringIndex = 0;
	
	for(stringIndex = 0; stringIndex < (int)strlen(string); stringIndex++)
	{
		/* skip if its a space */
		if(string[stringIndex] == ' ')
		{
			continue;
		}
		
		/* lowercase letters start from 97 */
		if(string[stringIndex] <= 96)
		{
			/* uppercase letters start from 65 */
			string[stringIndex] += 32;
		}
	}
}

/* encode or decode strings based on a given key */
void vigenere(char *string, char *key, enum CODE_METHOD method, int passes)
{
	int currPass = 0;
	int stringIndex = 0;
	int keyIndex = 0;
	int alphabetIndex = 0;
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	
	toLowercase(string);
	toLowercase(key);
	
	/* repeat the algorithm a set number of times */
	for(currPass = 0; currPass < passes; currPass++)
	{
		stringIndex = 0;
		keyIndex = 0;
		
		/* encode */
		if(method == ENCODE)
		{
			/* go through entire string */
			for(stringIndex = 0; stringIndex < (int)strlen(string); stringIndex++)
			{
				/* skip if its a space */
				if(string[stringIndex] == ' ')
				{
					continue;
				}
				
				/* find the encoded letter and set it to the corresponding string letter */
				alphabetIndex = ((string[stringIndex] % 97) + (key[keyIndex] % 97)) % 26;
				string[stringIndex] = alphabet[alphabetIndex];

				/* update the current key letter */
				keyIndex++;
				
				/* make sure the key index is within bounds */
				if(keyIndex >= (int)strlen(key))
				{
					keyIndex = 0;
				}
			}
		}
		/* decode */
		else if(method == DECODE)
		{
			/* go through entire string */
			for(stringIndex = 0; stringIndex < (int)strlen(string); stringIndex++)
			{
				/* skip if its a space */
				if(string[stringIndex] == ' ')
				{
					continue;
				}
				
				/* find the original letter and set it to the corresponding string letter; make sure it isn't negative */
				alphabetIndex = ((string[stringIndex] % 97) - (key[keyIndex] % 97)) % 26;
				if(alphabetIndex < 0)
				{
					alphabetIndex = 26 + alphabetIndex;
				}
				string[stringIndex] = alphabet[alphabetIndex];
				
				/* update the current key letter */
				keyIndex++;
				
				/* make sure the key index is within bounds */
				if(keyIndex >= (int)strlen(key))
				{
					keyIndex = 0;
				}
			}
		}
	}
	
	return;
}


/****************
main.c
By: Deepti Ramani
Date: 02/19/2020
Brief: The test file to use with vigenereCipher.c.  You will need to set it up to take input from the console for both the string to encrypt and the key to encrypt with, please use the provided arrays!  After encrypting also test the decrypting! 
gcc -O -Wall -Wextra -ansi -pedantic -o vcipher vigenereCipher.c main.c
****************/
#include <stdio.h>
#include "vigenereCipher.h"
#include <string.h>

int main(void)
{
	char string[256];
	char key[32];
	int passes;
	
	/*ask for the string to encrypt and store it in string */
	printf("What string would you like to encrypt?\n");
	fgets(string, 256, stdin);

	/*ask for the key to encrypt with and store it in key */
	printf("What key would you like to encrypt with?\n");
	fgets(key, 32, stdin);
	
	/* replace \n with nul terminator */
	string[strlen(string) - 1] = '\0';
	key[strlen(key) - 1] = '\0';
	
	/*ask for how many passes to encrypt with */
	printf("How many passes would you like to encrypt with?\n");
	scanf(" %i", &passes);
	
	/*encrypt string with the key, make sure set to encode! */
	vigenere(string, key, ENCODE, passes);		
	
	/*print out the encoded string */
	printf("encoded string: %s\n", string);
	
	/*now reverse it back to normal by setting it to decode */
	vigenere(string, key, DECODE, passes);

	/* print out the decoded string */
	printf("decoded string: %s\n", string);

	return 0;
}
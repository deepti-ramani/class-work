/*******************************************************************************
spellcheck.c
by Deepti Ramani
05/04/2020
Description: This file contains functions that read information from a dictionary file and check the properties/characteristics of different words.

gcc -O -Wall -Wextra -ansi -pedantic driver.c spellcheck.c -o spell.exe
*******************************************************************************/
#include <string.h>
#include <stdio.h>

/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h"

char *mystrupr(char *string)
{
	int i;
	/* iterate through each char in the string */
	for(i = 0; string[i] != '\0'; i++)
	{
		/* check if its lowercase */
		if(string[i] > 96 && string[i] < 123)
		{
			/* convert to uppercase */
			string[i] -= 32;
		}
	}
	return string;
}

char *remove_new_line(char *string)
{
	int index = strlen(string) - 1;
	if(string[index] == '\n')
	{
		string[index] = 0;
	}
	return string;
}

int minOf3(int a, int b, int c)
{
	if (a <= b && a <= c)
	{
		return a;
	}
	else if (b <= a && b <= c)
	{
		return b;
	}
	return c;
}

int get_distance(char* str1, char* str2, int str1len, int str2len)
{
	/* iteration */
	int i, j;
	/* costs */
	int insertion, deletion, replacement;
	
	/* create a 2d array to store distances between letters */
	int dist[str1len + 1][str2len + 1];

	/* fill in first column */
	for(i = 0; i < str1len + 1; i++)
	{
		dist[i][0] = i;
	}
	
	/* fill in first row */
	for(j = 0; j < str2len + 1; j++)
	{
		dist[0][j] = j;
	}
	
	/* use levenshtien's algorithm to fill in the rest of the array */
	for(i = 1; i < str1len + 1; i++)
	{
		for(j = 1; j < str2len + 1; j++)
		{		
			/* compare the string characters; if they are equal, then the cost/distance doesn't change */
			if(str1[i - 1] == str2[j - 1])
			{
				dist[i][j] = dist[i - 1][j - 1];
			}
			/* if the characters are different, we need to calculate the new distance */
			else
			{
				/* if we insert, the new distance is the distance to the char we are inserting */
				insertion = dist[i][j - 1];
				/* if we delete, the new distance is the distance to char corresponding to what we want to delete */
				deletion = dist[i - 1][j];
				/* if we replace, the distance doesn't technically change, but we're still performing an action */
				replacement = dist[i - 1][j - 1];
				
				/* select the shortest distance and add one b/c we're performing an "action" (cost is 1) */
				dist[i][j] = minOf3(insertion, deletion, replacement) + 1;
			}
		}
	}
	
	/* return the dist between the two words (bottom right element in the array) */
	return dist[str1len][str2len];
}

int info(const char *dictionary, struct DICTIONARY_INFO *dinfo)
{
	char nextWord[LONGEST_WORD];
	int longest = 0;
	int shortest = LONGEST_WORD;
	int count = 0;
	
	/* read from the file */
	FILE* dict = fopen(dictionary, "rt");
	
	/* make sure we can open the file */
	if(dict != NULL)
	{
		/* read entries until we're at the end of the file */
		while(!feof(dict))
		{
			/* get the next word */
			fgets(nextWord, LONGEST_WORD, dict);
			remove_new_line(nextWord);
			
			/* update count, shortest, longest if applicable */
			count++;
			
			if((int)strlen(nextWord)> longest)
			{
				longest = (int)strlen(nextWord);
			}
			
			if((int)strlen(nextWord) < shortest)
			{
				shortest = (int)strlen(nextWord);
			}
		}
		
		/* update dictionary info struct */
		dinfo->shortest = shortest;
		dinfo->longest = longest;
		dinfo->count = count;
		
		/* return FILE_OK when we're done reading the file */
		fclose(dict);
		return FILE_OK;
	}
	
	/* if file doesn't open, return FILE_ERR_OPEN */
	return FILE_ERR_OPEN;
}

int word_lengths(const char *dictionary, int lengths[], int count)
{
	int i;
	int numWords = 0;
	char nextWord[LONGEST_WORD];
	
	/* read from the file */
	FILE* dict = fopen(dictionary, "rt");
	
	/* make sure we can open the file */
	if(dict != NULL)
	{
		/* repeat for each length */
		for(i = 1; i <= count; i++)
		{
			dict = fopen(dictionary, "rt");
			
			/* read entries until we reach the file end */
			while(!feof(dict))
			{
				/* get the next word */
				fgets(nextWord, LONGEST_WORD, dict);
				remove_new_line(nextWord);
				
				/* check if the word length is equal to the current length we're checking for */
				if((int)strlen(nextWord) == i)
				{
					numWords++;
				}
			}
			/* store total number of words of that length */
			fclose(dict);
			lengths[i] = numWords;
			numWords = 0;
		}
		
		/* return FILE_OK when we're done recording lengths */
		return FILE_OK;
	}
	
	/* if we can't open the file, return FILE_ERR_OPEN */
	return FILE_ERR_OPEN;
}

int word_lengths_efficient(const char* dictionary, int lengths[], int count)
{
	char nextWord[LONGEST_WORD];
	int nextWordLength;
	
	/* read from the file */
	FILE* dict = fopen(dictionary, "rt");
	
	/* make sure we can open the file */
	if(dict != NULL)
	{
		/* read entries until we reach the file end */
		while(!feof(dict))
		{
			/* get the next word */
			fgets(nextWord, LONGEST_WORD, dict);
			remove_new_line(nextWord);
			nextWordLength = (int)strlen(nextWord);
			
			/* check if the word length is less than or equal to the max word length we're looking for */
			if(nextWordLength <= count)
			{
				lengths[nextWordLength - 1]++;
			}
		}
		fclose(dict);
		
		/* return FILE_OK when we're done recording lengths */
		return FILE_OK;
	}
	
	/* if we can't open the file, return FILE_ERR_OPEN */
	return FILE_ERR_OPEN;
}

int words_starting_with(const char *dictionary, char letter)
{
	int numWords = 0;
	char nextWord[LONGEST_WORD];
	
	/* read from the file */
	FILE* dict = fopen(dictionary, "rt");
	
	/* turn letter uppercase */
	if(letter > 96 && letter < 123)
	{
		letter -= 32;
	}
	
	/* make sure we can open the file */
	if(dict != NULL)
	{
		/* read entries until we reach the file end */
		while(!feof(dict))
		{
			/* get the next word */
			fgets(nextWord, LONGEST_WORD, dict);
			mystrupr(nextWord);
			
			/* stop searching if we've gone past the letter (sorted alphabetically) */
			if(nextWord[0] > letter)
			{
				break;
			}
			
			/* if the word starts with the right letter, increment counter */
			if(nextWord[0] == letter)
			{
				numWords++;
			}
		}
		
		/* return how many words start with that letter once we're done reading the file */
		fclose(dict);
		return numWords;
	}
	
	/* if the file doesn't open, return FILE_ERR_OPEN */
	return FILE_ERR_OPEN;
}

int spell_check(const char *dictionary, const char *word)
{	
	char nextWord[LONGEST_WORD];
	char uprWord[LONGEST_WORD];
	
	/* read from the file */
	FILE* dict = fopen(dictionary, "rt");
	
	/* make sure that the case isn't counted as a difference in the word */
	strcpy(uprWord, word);
	mystrupr(uprWord);
		
	/* make sure we can open the file */
	if(dict != NULL)
	{
		/* read entries until we reach the file end */
		while(!feof(dict))
		{
			/* get the next word and make it uppercase to compare */
			fgets(nextWord, LONGEST_WORD, dict);
			remove_new_line(nextWord);
			mystrupr(nextWord);
			
			/* make sure we haven't gone past the letter (since its sorted alphabetically) */
			if(nextWord[0] > uprWord[0])
			{
				break;
			}
			
			/* check if the words match */
			if(strcmp(nextWord, uprWord) == 0)
			{
				return WORD_OK;
			}
		}
		
		/* if the word doesn't match anything in the dictionary, return WORD_BAD */
		fclose(dict);
		return WORD_BAD;
	}
	
	/* if we can't open the file, return FILE_ERR_OPEN */
	return FILE_ERR_OPEN;
}

int closest_word(const char *dictionary, const char *word, int deviation)
{
	char nextWord[LONGEST_WORD];
	char uprWord[LONGEST_WORD];
	int dist = 0;
	
	/* read from the file */
	FILE* dict = fopen(dictionary, "rt");
	
	/* remove case as a difference between the words */
	strcpy(uprWord, word);
	mystrupr(uprWord);
	
	/* make sure the file can be opened */
	if(dict != NULL)
	{
		while(!feof(dict))
		{
			/* get the next word to check against and remove the newline character*/
			fgets(nextWord, LONGEST_WORD, dict);
			remove_new_line(nextWord);
			mystrupr(nextWord);
			
			/* make sure we haven't gone past the letter (since its sorted alphabetically) */
			if(nextWord[0] > uprWord[0])
			{
				break;
			}

			/* check if the words are close and print result/return if they are */
			dist = get_distance(nextWord, uprWord, strlen(nextWord), strlen(uprWord));
			if(dist <= deviation)
			{
				fclose(dict);
				printf("you entered %s. Did you mean %s?\n", uprWord, nextWord);
				return FILE_OK;
			}		
		}
		
		/* if we can't find our word at all, print and return */
		fclose(dict);
		printf("Could not find any matches for %s\n", uprWord);
		return FILE_OK;
	}
	
	/* if we can't open the file, return FILE_ERR_OPEN */
	return FILE_ERR_OPEN;
}
/* 
example.c
by Deepti Ramani
05/11/2020
Introduction of dynamic memory allocation 

gcc -Wall -Wextra -Werror -ansi -pedantic -O example.c -o test.exe
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int numChars;
	char* str;
	FILE* fp = fopen("Goblet1.txt","rt");
	
	/* check if file exists */
	if(fp != NULL)
	{
		/* the number of chars in the chapter is given in line 1 */
		fscanf(fp, "%d", &numChars);
		str = (char*) malloc(numChars * sizeof(char));
		
		/* "get rid of" the rest of line 1 if it isn't already there*/
		fgets(str, numChars, fp);
		
		/* go through entire file and copy into str */
		fread(str, numChars, sizeof(char), fp);
		
		printf("%s", str);		
		fclose(fp);
		return 0;
	}
	
	/* return -1 if null */
	return -1;
}
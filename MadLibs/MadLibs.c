/*
MadLibs.c
by Deepti Ramani
Last Edited: 09/09/2019
Description: Reads (a lot of) input from user and prints a madlib using that input.

gcc -Wall -Wextra -ansi -pedantic Madlibs.c -o madlib
*/

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 64

int main(void)
{
	/* Create variables to hold madlib input values */
	char user[MAX_LENGTH];
	
	char location[MAX_LENGTH];
	char adj[MAX_LENGTH];
	
	char animal1[MAX_LENGTH];
	char verb1[MAX_LENGTH];
	char animal2[MAX_LENGTH];
	char verb2[MAX_LENGTH];
	char emotion1[MAX_LENGTH];
	
	char time[MAX_LENGTH];
	char bodyPart[MAX_LENGTH];
	char transport[MAX_LENGTH];
	char emotion2[MAX_LENGTH];
	
	char noun[MAX_LENGTH];
	int number;
	char adj2[MAX_LENGTH];

	/* Ask player for input */
	printf("Please enter a name: ");
	fgets(user, MAX_LENGTH, stdin);
	user[strlen(user)-1] = 0;

	printf("Please enter a location: ");
	fgets(location, MAX_LENGTH, stdin);
	location[strlen(location)-1] = 0;
	
	printf("Please enter an adjective: ");
	fgets(adj, MAX_LENGTH, stdin);
	adj[strlen(adj)-1] = 0;
	
	printf("Please enter the name of an animal (plural): ");
	fgets(animal1, MAX_LENGTH, stdin);
	animal1[strlen(animal1)-1] = 0;
	
	printf("Please enter a verb ending in -ing: ");
	fgets(verb1, MAX_LENGTH, stdin);
	verb1[strlen(verb1)-1] = 0;
	
	printf("Please enter the name of an animal (plural): ");
	fgets(animal2, MAX_LENGTH, stdin);
	animal2[strlen(animal2)-1] = 0;
	
	printf("Please enter a verb ending in -ing: ");
	fgets(verb2, MAX_LENGTH, stdin);
	verb2[strlen(verb2)-1] = 0;
	
	printf("Please enter an emotion: ");
	fgets(emotion1, MAX_LENGTH, stdin);
	emotion1[strlen(emotion1)-1] = 0;
	
	printf("Please enter a body part: ");
	fgets(bodyPart, MAX_LENGTH, stdin);
	bodyPart[strlen(bodyPart)-1] = 0;
	
	printf("Please enter a period of time: ");
	fgets(time, MAX_LENGTH, stdin);
	time[strlen(time)-1] = 0;
	
	printf("Please enter a mode of transportation: ");
	fgets(transport, MAX_LENGTH, stdin);
	transport[strlen(transport)-1] = 0;
	
	printf("Please enter an emotion: ");
	fgets(emotion2, MAX_LENGTH, stdin);
	emotion2[strlen(emotion2)-1] = 0;
		
	printf("Please enter a noun: ");
	fgets(noun, MAX_LENGTH, stdin);
	noun[strlen(noun)-1] = 0;
	
	printf("Please enter a number: ");
	scanf("%i", &number);
	
	printf("Please enter an adjective: ");
	fgets(adj2, MAX_LENGTH, stdin);
	adj2[strlen(adj2)-1] = 0;
	
	
	/* print the madlib */
	printf("\nThe Journey \na short story by %s\n", user);
	printf("\nEveryone should go to %s at least once in their lives.\n", location );
	printf("I remember my first trip. It was a %s summer day, and I was free as a bird. I decided to go somewhere exciting.\n", adj);
	printf("The second I stepped foot in %s, I knew it was the place for me.\n", location);
	printf("The %s were %s, the %s were %s, and I was %s.\n", animal1, verb1, animal2, verb2, emotion1);
	printf("I would sell my %s if I could have stayed in %s for more than %s, but unfortunately, I had to go home.\n", bodyPart, location, time);
	printf("It was a %s trip home, but the %s was comfortable and I passed the time by looking at the %s I bought as a souvenir.\n", emotion2, transport, noun);
	printf("I've probably gone to %s at least %i times by now, and I have so many trinkets from my journeys.\n", location, number);
	printf("Yet, my favorite souvenir will always be that %s %s that I bought on my very first trip.\n", adj2, noun);
	
	/* Quit */
	printf("\nThanks for playing! Press enter to quit!");
	getchar();
	
	return 0;
}

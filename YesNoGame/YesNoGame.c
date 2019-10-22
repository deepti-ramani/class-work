/****************************
Filename: YesNoGame.c
Name: Deepti Ramani
Date Last Edited: 16 Sep. 2019
Brief Description: A yes or no game where the player is the guidance counselor of a school
gcc -Wall -Wextra -Werror -ansi -pedantic -O YesNoGame.c -o yesnogame.exe
****************************/
/*printf, scanf*/
#include <stdio.h>
/*rand, srand*/
#include <stdlib.h>
/*time*/
#include <time.h>

#define INTRO_EVENT -1

/* need to fix random mysterious student */
int main(void)
{
	/*valid inputs will be y, n, and q to quit*/
	char input;
	
	/*-1 descibes the starter event*/
	int eventID = INTRO_EVENT;
	
	/*5 events*/
	int maxEventID = 5;
	
	/* game variables: number of students (population), motivation (happiness), effort (currency) */
	int numStudents = 20;
	
	int motivation = 100;
		int motivationIncrease = 0; /* tracks change in motivation for evaluations */
		int motivCount = 1;	/* interval for checking student increase */
	
	int effort = 100;
	
	/* for pay cut/pay raise */
	int countBadEvaluations = 0;
	int countGoodEvaluations = 0;
	
	/* list of all students, integer represents individual studets' motivation */
	int count = 0;	/* keep track of current student */
	int studentList[ 20 ] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	char studentNames[26][15] = {"Alice", "Bobby", "Carson", "Diane", "Emma", "Fiona", "Gary", "Helena", "Ian", "Janice", "Kelly", "Leo", "Marvin", "Nicole", "Oliver", "Pauline", "Quentin", "Rose", "Steve", "Trevor", "Uma", "Victor", "Wendy", "Xavier", "Yelena", "Zara" };
	
	/* mysterious student's names */
	int random = 0;
	char mysteriousStudentPool[8][15] = { "Dmitri", "Esmeralda", "Faye", "Felicia", "Elizabeth", "Angelina", "Benjamin" , "Celestine" };
	
	/*variables for skipping student event */
	int studentSkippingEvent = 0;	/* is the event happening or not */
	int skippingStudentID = -1;	/* keeps track of which student is in trouble */
	
	/* variables for the mysterious student event */
	int mysteriousNameID = -1;	/* keeps track of mysterious student's name for one game */
	int mysteriousStudent = 0; 	/* stores if you know their name */
	
	/*set a seed using time*/
	srand(time(NULL));
	
	/*Add the introduction to the game here, explain the rules to user */
	
	do
	{
		/*setting input to 'a' resets the input*/
		input = 'a';
		/*switch on the event, in each have something desribe what the options are (y/n)*/
		switch(eventID)
		{
			case INTRO_EVENT:
				printf("Hello, and welcome to Redmond High School! You must be our new guidance counselor.\n");
				printf("My name is Jeffrey Geoffrey, and I'm the principal here. Let me show you around.\n");
				printf("Your job is to help as many students as possible. Make sure they're motivated and on track to graduate.\n");
				printf("You're only one person, so its important that you manage your time and effort between students.\n");
				printf("These students need all the help they can get. Are you ready?\n");
				break;
			
			/* switch classes */	
			case 0:
				printf("%s: I need to take a different class to graduate. Can you help me change my schedule?\n", studentNames[count]);
				break;
			
			/* rec */
			case 1:
				printf("%s: Can you write a letter of recommendation for me?\n", studentNames[count]);
				break;
			
			/* mystery student */
			case 2:
				if(mysteriousStudent != 1)
				{
					mysteriousNameID = random;
					printf("???: Hello... would you like to know my name?\n");
				}
				else
				{
					printf("%s: Do you want me to predict your future?\n", mysteriousStudentPool[mysteriousNameID]);
				}
				break;
		
			/* skipping student */
			case 3:
				/* ask about meeting */
				if(studentSkippingEvent == 0)
				{
					skippingStudentID = count;
					printf("Principal Geoffrey: I found %s skipping class. Will you talk some sense into them?\n", studentNames[skippingStudentID]);
				}
				/* the actual meeting */
				else if(studentSkippingEvent == 1)
				{
					printf("%s: Principal Geoffrey said I should talk to you about skipping class?\n", studentNames[skippingStudentID]);
				}
				break;
			
			/* evaluation */
			case 4:
				printf("Principal Geoffrey: I just thought I'd check in on how you were doing.\n Would you like me to give you your evaluation?\n");
				break;
				
			/* pay cut */
			case 5:
				printf("Principal Geoffrey: So, have you heard the bad news?\n");
				break;
		}
		
		
		/*accept a character as input q quits everyting else should be n or y if none keep checking*/
		while(input != 'n' && input != 'y'&& input != 'q')
		{
			printf("\nEnter 'y' for yes or 'n' for no ('q' to quit): ");
			/*scanf goes here*/
			scanf(" %c", &input);
			printf("\n");
			
		}
		
		/*switch on the event change outcome based on input*/
		switch(eventID)
		{
			/* response to intro */
			case INTRO_EVENT:
				if(input == 'y')
				{
					printf("That's the spirit!\n");
				}
				else if(input == 'n')
				{
					printf("Well, that's unfortunate. I guess I'd better find another guidance counselor...\n");
					input = 'q';
				}
				break;
				
			/* switch classes */
			case 0:
				if(input == 'y')
				{
					printf("%s: Thanks for your help! I'm glad I'm on track to graduate!\n", studentNames[count]);
					studentList[count] += 10;
					motivation += 10;
					motivationIncrease += 10;
					effort -= 5;
				}
				else if(input == 'n')
				{
					printf("%s: Now I'll never meet those graduation requirements...\n", studentNames[count]);
					studentList[count] -= 5;
					motivation -= 5;
					motivationIncrease -= 5;
					
					/* check if student should drop out (motivation) */
					if(studentList[count] <= 0)
					{
						/* "remove" that student, reduce student total, print message */
						studentList[count] = 0;
						numStudents--;
						printf("%s: This is the last straw! I'm dropping out!\n", studentNames[count]);
					}
				}
				break;
			
			/* recommendation */
			case 1:

				if(input == 'y')
				{
					printf("%s: Thank you so much! This means a lot!\n", studentNames[count]);
					effort -= 15;
					studentList[count] += 15;
					motivation += 15;
					motivationIncrease += 15;
				}
				else if(input == 'n')
				{
					printf("%s: Aw, now I have to go find someone else...\n", studentNames[count]);
					studentList[count] -= 5;
					motivation -= 5;
					motivationIncrease -= 5;
					/* check if student should drop out (motivation) */
					if(studentList[count] <= 0)
					{
						/* "remove" that student, reduce student total, print message */
						studentList[count] = 0;
						numStudents--;
						printf("%s: This is the last straw! I'm dropping out!\n", studentNames[count]);
					}
				}
				break;
				
			/* mysterious student */
			case 2:
				if(input == 'y')
				{
					/* if you need to know name */
					if(mysteriousStudent == 0)
					{
						mysteriousStudent = 1;
						mysteriousNameID = random;
						printf("???: Very well... I am %s. We will meet again soon...", mysteriousStudentPool[mysteriousNameID]);
					}
					/* if you already know name */
					else if (mysteriousStudent == 1)
					{
						if(numStudents % 2 == 0)
						{
							if(rand() % 5 > 3)
							{
								printf("%s: I sense great prosperity in your future. Make sure you avoid the mystery meat in the cafeteria...\n", mysteriousStudentPool[mysteriousNameID]);
								effort += 15;
							}
							else
							{
								printf("%s: Oh, dear... You should be careful...\n", mysteriousStudentPool[mysteriousNameID]);
								effort -= 7;
							}
						}
						else
						{
							if(rand() % 5 == 1)
							{
								printf("%s: Hmm... I'd rather not say...\n", mysteriousStudentPool[mysteriousNameID]);
							}
							else
							{
								printf("%s: I'm not positive, but things will go well if you don't anger anyone...", mysteriousStudentPool[mysteriousNameID]);
								effort += 7;
							}
						}
					}
				}
				else if(input == 'n')
				{
					/* need to know name */
					if(mysteriousStudent == 0)
					{
						printf("???: I'll be back...\n");
					}
					/* already know name */
					else if(mysteriousStudent == 1)
					{
						printf("%s: Perhaps another time...\n", mysteriousStudentPool[mysteriousNameID]);
					}
				}
				break;
				
			/* skipping student */
			case 3:
				switch(studentSkippingEvent) {
					/* setting up meeting */
					case 0:
						/* agree to meeting */
						if(input == 'y')
						{
							printf("Principal Geoffrey: Very well, I'm sure they'll come by soon.\n");
							
							/* ready for follow up meeting */
							studentSkippingEvent = 1;
						}
						
						/* say no to meeting: lower motivation + chance of dropping out*/
						else if(input == 'n')
						{
							printf("Principal Geoffrey: Alright then... I guess you don't have enough time for poor %s.\n", studentNames[skippingStudentID]);
							studentList[skippingStudentID] -= 2;
							motivationIncrease -= 2;
							motivation -= 2;
							
							/* check if student should drop out (motivation) */
							if(studentList[skippingStudentID] <= 0)
							{
								/* "remove" that student, reduce student total, print message */
								studentList[skippingStudentID] = 0;
								numStudents--;
								printf("%s: Nobody here believes in me! I'm dropping out!\n", studentNames[skippingStudentID]);
							}
						}
						break;
						
					/* a */
					case 1:			
						/* event over, start again */
						if(input == 'y'){
							/* success: gain motivation & effort */
							if(rand() % 10 > 2)
							{
								printf("%s: I'm a good kid, I swear! I just made a mistake...\n", studentNames[skippingStudentID]);
								printf("...\n...\n...\n...\n");
								printf("%s: Thanks for listening. I'd like to give you this gift card!\n", studentNames[skippingStudentID]);
								effort += 60;
								studentList[skippingStudentID] += 13;
								motivation += 13;
								motivationIncrease += 13;
							}
							/* failure: lose motivation & effort */
							else
							{
								printf("%s: Alright let's get this over with...", studentNames[skippingStudentID]);
								printf("...\n...\n...\n...\nThey stormed out...\n");
								motivation -= 8;
								studentList[skippingStudentID] -= 8;
								motivationIncrease -= 8;
								effort -= 10;
							}
							studentSkippingEvent = 0;
						}
						else if(input == 'n')
						{
							/* keeps looping this step */
							printf("%s: Alright, I'll come back later.\n", studentNames[skippingStudentID]);
							studentSkippingEvent = 1;
						}
						break;
				}
				break;				
				
			/* evalutation */
			case 4:
				if(input == 'y')
				{
					printf("Principal Geoffrey: Very well, then.\n");
					/* pay raise or cut */
					if(motivationIncrease >= 50)
					{
						if(rand() % 3 == 1)
						{
							printf("Your students are very motivated, and I happen to be in a good mood. You're getting a massive pay raise!!!\n");
							effort += 50 * (motivation / 150);
							countGoodEvaluations++;
							motivationIncrease = 0;
						}
						else
						{
							printf("Your students are very motivated, and you're doing a decent job. I think I'll give you a raise!\n");
							effort += 30 * (motivation / 150);
							countGoodEvaluations++;
							motivationIncrease = 0;
						}
					}
					else
					{
						printf("You should try to keep your students more motivated. I think you might be spread too thin...\n");
						numStudents -= 5;
						countBadEvaluations++;
						motivationIncrease = 0;
					}
				}
				else if(input == 'n')
				{
					printf("Principal: What a dissappointment. Well, I'd better come back later...\n");
				}
				break;
				
			/* pay cut */
			case 5:
				if(input == 'y'){
					/* if you have more bad evaluations */
					if(countGoodEvaluations - countBadEvaluations < 0)
					{
						printf("Principal Geoffrey: So you do know about your pay cut. Well, with the number of bad evaluations you've had, it was bound to happen eventually.\n");
						effort -= 10;
					}
					/* if you have equal good & bad (and you've had at least one bad) */
					else if(countGoodEvaluations - countBadEvaluations == 0 && countBadEvaluations != 0)
					{
						printf("Principal Geoffrey: That's right - you're cutting it pretty close! A couple more bad evaluations, and you'll be getting a pay cut.\n");
					}
					/* if you have more good evaluations */
					else
					{
						printf("Principal Geoffrey: Oh, really? Well, I guess I don't need to be here, then.\n");
					}
				}
				else if(input == 'n')
				{
					if(rand() % 5 > 3)
					{
						printf("Well, now I feel awkward...I'm going to leave, now.\n");
					}
					else
					{
						/* if you have more bad evaluations */
						if(countGoodEvaluations - countBadEvaluations < 0)
						{
							printf("Principal Geoffrey: You haven't guessed? You've had one too many bad evaluations, so we're lowering your salary.\n");
							effort -= 13;
						}
						/* if you have equal good & bad (and you've had at least one bad) */
						else if(countGoodEvaluations - countBadEvaluations == 0 && countBadEvaluations != 0)
						{
							printf("Principal Geoffrey: Then let me make it very clear: you've made it by the skin of your teeth. A couple more bad evaluations, and you'll be getting a pay cut.\n");
						}
						/* if you have more good evaluations */
						else
						{
							printf("Principal Geoffrey: Ahahahahaha! Don't be so nervous! I'm messing with you! You're doing a great job!\n");
						}
					}
				}
				break;
		}
		
		/* check if you gained students */
		if(motivation / (150 * motivCount) == 1)
		{
			motivCount++;
			printf("\nYou're doing a great job keeping you're students motivated. \nYou gained 5 new students!\n");
			numStudents += 5;
		}
		
		/* need effort */
		if(effort <= 0)
		{
			printf("\nIt looks like you're spread too thin. Better get rid of some of your students...\n");
			if(numStudents > 5)
			{
				numStudents -= 5;
				effort += 50;
			}
			else if(numStudents > 1)
			{
				numStudents = 1;
				effort += ((numStudents - 1) * 10);
			}
			else
			{
				numStudents = 0;
				effort += 10;
			}
		}
		
		/* fired */
		if(numStudents <= 0)
		{
			printf("\nYou have no more students. You are fired.\n");
			input = 'q';
		}
				
		/* after each interaction, update variables */
		if(input == 'q')
		{
			printf("\nFinal Results: ");
		}
		printf("\nNumber of Students: %i \nMotivation: %i \nEffort: %i \n", numStudents, motivation, effort);
		
		/* randomly decides next student's name */
		count = (rand() % 26);
		/* decides mystery student's name (changes depending on when you get the event) */
		random = (rand() % 8);
		
		/*reset event id with rand*/
		eventID = rand() % (maxEventID + 1);
		getchar();
		getchar();
		
	} while(input != 'q');
	
	
	return 0;
}


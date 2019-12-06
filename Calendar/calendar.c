/**************************
calendar.c
By: Deepti Ramani
Date: 12/05/2019
Brief: This file will be used to determine if a year is a leap year, find the day of the week given a day/month/year, and print a calendar using the is_leapyear and day_of_the_week functions.
**************************/

#include <stdio.h>

#define TRUE  1
#define FALSE 0

int is_leapyear(int year)
{
	/* divisible by 400 */
	if (!(year % 400))
	{
		return TRUE;
	}
	/* divisible by 4 but not 100 */
	else if (!(year % 4) && (year % 100))
	{
		return TRUE;
	}
	/* if it gets here, it isn't a leap year */
	return FALSE;
}

int day_of_the_week(int day, int month, int year)
{
	int temp = 0;
	int month_keys[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
	int year_keys[] = {4, 2, 0, 6};
	
	temp = (year % 100) / 4 + day;
	
	temp += month_keys[month - 1];
	
	if(month < 3 && is_leapyear(year))
	{
		temp -= 1;
	}
	
	while (year > 2099)
	{
		year -= 400;
	}
	
	temp += year_keys[(year / 100) - 17];
	temp += year % 100;
	temp %= 7;
	/* account for saturday */
	if (temp == 0)
	{
		temp = 7;
	}
	return temp;
}

void print_calendar(int month, int year)
{
	int day = 1;
	int col = 0;
	int first_day_of_week;
	int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char *months[] = {"January",   "February", "March",    "April", 
					"May",       "June",     "July",     "August",
					"September", "October",  "November", "December"};

	/* Print calendar header */
	printf("%s, %i\n", months[month - 1], year);
	printf("Su Mo Tu We Th Fr Sa\n");
	printf("---------------------\n");
	
	/* print leading spaces of first row */
	first_day_of_week = day_of_the_week(1, month, year);
	while(col < first_day_of_week - 1)
	{
		printf("   ");
		col++;
	}
	
	/* print remaining rows */
	for(; col < 7; col++)
	{
		/* one-digit numbers */
		if(day < 10)
		{
			printf(" %i ", day);
		}
		/* two-digit numbers */
		else
		{
			printf("%i ", day);
		}
		
		/* new line every 7th day */
		if(col == 6)
		{
			printf("\n");
			col = -1;
		}
		
		/* stop printing days if the number of days in the month has been reached*/
		if(day == days_in_month[month - 1])
		{
			break;
		}
		day++;
	}
	printf("\n");
}

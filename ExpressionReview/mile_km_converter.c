/*
mile_km_converter.c
by Deepti Ramani
12/9/2019
program that converts between miles and kilometers

gcc -Wall -Wextra -Werror -ansi -pedantic -O mile_km_converter.c -o mile_km_converter.exe
*/

/* printf, scanf */
#include <stdio.h>

double convertToKm(double miles)
{
	return miles * 1.60934;
}

double convertToMiles(double km)
{
	return km / 1.60934;
}

int main(void)
{
	char input;
	float num;
	printf("Print 'm' to convert miles to kilometers and 'k' to convert kilometers to miles: ");
	scanf(" %c", &input);
	while(input != 'm' && input != 'k')
	{
		printf("Invalid input. Please print 'm' to convert miles to kilometers and 'k' to convert kilometers to miles: ");
		scanf(" %c", &input);
		
	}
	printf("Enter the number to be converted: ");
	scanf(" %f", &num);
	if(input == 'm')
	{
		printf("Your number in kilometers: %.5f\n", convertToKm(num));
	}
	else
	{
		printf("Your number in miles: %.5f\n", convertToMiles(num));
	}
	return 0;
}
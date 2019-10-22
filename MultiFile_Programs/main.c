/* printf */
#include <stdio.h>
/* AddIntegers, SubtractIntegers */
#include "my_math.h"

int main(void)
{
	int first = 7;
	int second = 2;
	printf("%i + %i = %i\n", first, second, AddIntegers(first, second));
	printf("%i - %i = %i\n", first, second, SubtractIntegers(first, second));
	return 0;
}


/*****
fractions.h
By: Definitely Someone
Last Edited: 2/19/2020
Description: The header file for fractions.c, contains all function prototypes and the definitions of the structures to be used in the lab
*****/

struct FRACTION
{
  int numerator;
  int denominator;
};

struct MIXED_FRACTION
{
  int whole_number;
  struct FRACTION proper_fraction;
};

struct FRACTION add_fractions(const struct FRACTION *a, const struct FRACTION *b);
struct FRACTION subtract_fractions(const struct FRACTION *a, const struct FRACTION *b);
struct FRACTION multiply_fractions(const struct FRACTION *a, const struct FRACTION *b);
struct MIXED_FRACTION reduced_to_mixed(const struct FRACTION *fraction);
int GCD(int a, int b);
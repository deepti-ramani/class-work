/****************
vigenereCipher.h
By:Ryan Scheppler
Date: 1/15/18
Brief: the header file to use with vigenereCipher.c
****************/

enum CODE_METHOD {ENCODE, DECODE};

void toLowercase(char *string);

void vigenere(char *string, char *key, enum CODE_METHOD method, int passes);
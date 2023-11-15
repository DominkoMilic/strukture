#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)

struct _Poly;
typedef struct _Poly* Position;
typedef struct _Poly {
	int coefficient;
	int exponent;
	Position next;
} poly;

int readFile(char* fileName, Position headPoly1, Position headPoly2);

int main()
{
	poly headPoly1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	poly headPoly2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	char* fileName = "poly.txt";


	return EXIT_SUCCESS;
}


int readFile(char* fileName, Position headPoly1, Position headPoly2)
{
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "r");



	return EXIT_SUCCESS;
}


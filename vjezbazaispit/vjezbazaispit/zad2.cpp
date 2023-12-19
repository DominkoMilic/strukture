#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <stdlib.h>

struct _Cvor;
typedef struct _Cvor* Position;
typedef struct _Cvor {
	int element;
	Position next;
	Position previous;
} cvor;

int main()
{
	cvor head = { .element = 0,.next = NULL };


	return 0;
}
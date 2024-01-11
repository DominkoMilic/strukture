#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 50
#define MAX_LINE 1024

struct polinom;
typedef struct polinom* position;
typedef struct polinom{
	int coefficient;
	int exponent;
	position next;
} Polinom;

int ReadFile(position headPoly1, position headPoly2, char* fileName);
void InsertSorted(position head, int coefficient, int exponent);
int AddPolynomes(position addHead, position h1, position h2);
int MultiplyPolynomes(position resultHead, position h1, position h2);
void printList(position head); 
position CreateElement(int coefficient, int exponent);
void Merge(position resultHead);
void FreeMemory(position head);

int main() {
	Polinom headPoly1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Polinom headPoly2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Polinom headPolyAdd = { .coefficient = 0,.exponent = 0,.next = NULL };
	Polinom headPolyMultiply = { .coefficient = 0,.exponent = 0,.next = NULL };

	char* fileName = "polynomes.txt";
	if (ReadFile(&headPoly1, &headPoly2, fileName) == EXIT_SUCCESS) {
		printf("first poly:\n");
		printList(&headPoly1);
		printf("\nsecond poly:\n");
		printList(&headPoly2);
		AddPolynomes(&headPolyAdd, &headPoly1, &headPoly2);
		printf("\naddded poly:\n");
		Merge(&headPolyAdd);
		printList(&headPolyAdd);
		MultiplyPolynomes(&headPolyMultiply, &headPoly1, &headPoly2);
		printf("\nmultiplied poly:\n");
		Merge(&headPolyMultiply);
		printList(&headPolyMultiply);
	}

	FreeMemory(&headPoly1);
	FreeMemory(&headPoly2);
	FreeMemory(&headPolyAdd);
	FreeMemory(&headPolyMultiply);


	return 0;
}

int ReadFile(position headPoly1, position headPoly2, char* fileName) {
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int coefficient, exponent;

	filePointer = fopen(fileName, "r");
	if (!filePointer) {
		printf("Can't open file!\n");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < 2; ++i) {
		if (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
			char *token = strtok(buffer, " ");
			while (token != NULL) {
				if (sscanf(token, "%dx^%d", &coefficient, &exponent) == 2) {
					if (i == 0) {
						InsertSorted(headPoly1, coefficient, exponent);
					}
					else {
						InsertSorted(headPoly2, coefficient, exponent);
					}
				}
				token = strtok(NULL, " ");
			}
		}
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}


position CreateElement(int coefficient, int exponent) {
	position element = NULL;

	element = (position)malloc(sizeof(Polinom));
	if (!element) {
		printf("Can't allocate memory!\n");
		return NULL;
	}

	element->coefficient = coefficient;
	element->exponent = exponent;
	element->next = NULL;

	return element;
}

void InsertSorted(position head, int coefficient, int exponent) {
	position newNode = CreateElement(coefficient, exponent);
	position current = head;
	position previous = NULL;

	if (coefficient == 0)
		return;

	while (current != NULL && current->exponent < exponent) {
		previous = current;
		current = current->next;
	}

	if (previous == NULL) {
		newNode->next = head;
		head = newNode;
	}
	else {
		previous->next = newNode;
		newNode->next = current;
	}
}

void printList(position head) {
	position first = head->next;
	while (first != NULL) {
		printf("%dX^%d ", first->coefficient, first->exponent);
		first = first->next;
	}
}

int AddPolynomes(position addHead, position h1, position h2) {
	position current1 = h1;
	position current2 = h2;
	while (current1 != NULL)
	{
		InsertSorted(addHead, current1->coefficient, current1->exponent);
		current1 = current1->next;
	}
	while (current2 != NULL)
	{
		InsertSorted(addHead, current2->coefficient, current2->exponent);
		current2 = current2->next;
	}

	return EXIT_SUCCESS;
}

int MultiplyPolynomes(position resultHead, position h1, position h2) {
	position current1 = h1;
	position current2 = h2;

	while (current1 != NULL) {
		current2 = h2;

		while (current2 != NULL) {
			int coefficientMultiply, exponentAdd;
			coefficientMultiply = current1->coefficient * current2->coefficient;
			exponentAdd = current1->exponent + current2->exponent;
			InsertSorted(resultHead, coefficientMultiply, exponentAdd);
			current2 = current2->next;
		}

		current1 = current1->next;
	}


	return EXIT_SUCCESS;
}

void Merge(position resultHead) {
	while (resultHead->next != NULL) {
		int flag = 0;
		if (resultHead->exponent == resultHead->next->exponent) {
			resultHead->coefficient = resultHead->coefficient + resultHead->next->coefficient;
			position toDelete = resultHead->next;
			resultHead->next = toDelete->next;
			free(toDelete);
			flag = 1;
		}
		if(flag == 0)
			resultHead = resultHead->next;
	}
}

void FreeMemory(position head) {
	position current = head;
	position toDelete = NULL;
	while (current->next != NULL) {
		toDelete = current->next;
		current->next = toDelete->next;
		free(toDelete);
	}
}

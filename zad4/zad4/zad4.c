#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)
#define EMPTY_LISTS (-2)


struct _Element;
typedef struct _Element* Position;
typedef struct _Element
{
	int coefficient;
	int exponent;
	Position next;
} Element;

int readFile(Position headPoly1, Position headPoly2, char* fileName);
int printPoly(char* polynomeName, Position first);
int addPoly1(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);
int addPoly2(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);
int freeMemory(Position head);
Position createElement(int coefficient, int exponent);
int parseStringIntoList(Position head, char* buffer);
int insertSorted(Position head, Position newElement);
int deleteAfter(Position previous);
int mergeAfter(Position current, Position newElement);
int insertAfter(Position current, Position newElement);

int main()
{
	Element headPoly1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Element headPoly2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	char* fileName = "polynomes.txt";
	if (readFile(&headPoly1, &headPoly2, fileName) == EXIT_SUCCESS)
	{
		printf("1st polynome: ", headPoly1.next);
		printf("2nd polynome: ", headPoly2.next);
	}

	free(&headPoly1);
	free(&headPoly2);

	return EXIT_SUCCESS;
}


int readFile(Position headPoly1, Position headPoly2, char* fileName)
{
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;
	filePointer = fopen(fileName, "r");
	if (!filePointer)
	{
		printf("can't open file");
		return FILE_NOT_OPEN;
	}
	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(headPoly1, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(headPoly2, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int parseStringIntoList(Position head, char* buffer)
{
	char* currentBuffer = buffer;
	int coefficient = 0;
	int exponent = 0; 
	int numBytes = 0;
	int status = 0;
	Position newElement = NULL;
	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes);
		if (status != 2)
		{
			printf("this file is not good\n");
			return EXIT_FAILURE;
		}
		newElement = createElement(coefficient, exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}
		insertSorted(head, newElement);
		currentBuffer += numBytes;
	}
	return EXIT_SUCCESS;
}

Position createElement(int coefficient, int exponent)
{
	Position element = NULL;
	element = (Position)malloc(sizeof(Element));
	if (!element)
	{
		printf("can't allocate memory");
		return FAILED_MEMORY_ALLOCATION;
	}
	element->coefficient = coefficient;
	element->exponent = exponent;
	element->next = NULL;

	return element;
}

int freeMemory(Position head)
{
	Position current = head;
	while (current->next)
	{
		deleteAfter(current);
	}
	return EXIT_SUCCESS;
}

int deleteAfter(Position previous)
{
	Position toDelete = NULL;
	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int insertSorted(Position head, Position newElement)
{
	Position current = head;
	while (current->next != NULL && current->next->exponent > newElement->exponent)
	{
		current = current->next;
	}

	mergeAfter(current, newElement);

	return EXIT_SUCCESS;
}

int mergeAfter(Position current, Position newElement)
{

	if (current->next == NULL || current->next->exponent != newElement->exponent)
	{
		insertAfter(current, newElement);
	}
	else
	{
		int resultCoefficient = current->next->coefficient + newElement->coefficient;
		if (resultCoefficient == 0)
		{
			deleteAfter(current);
		}
		else
		{
			current->next->coefficient = resultCoefficient;
		}
		free(newElement);
	}
	return EXIT_SUCCESS;
}

int insertAfter(Position current, Position newElement)
{
	newElement->next = current->next;
	current->next = newElement;

	return EXIT_SUCCESS;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_LENGTH 50

struct _Numbers;
typedef struct _Numbers* Position;
typedef struct _Numbers {
	double value;
	Position next;
} numbers;


int readFileAndCalculate(char* fileName, Position head, double* result);
Position createNumber(double number);
int insertNumberInList(Position head, Position newNumber);
int calculate(char operation, double* result, Position head);
int toDelete(Position current);

int main()
{
	numbers head = { .value = 0.0,.next = NULL };
	double result = 0.0;
	char* fileName = "postfix.txt";
	if (readFileAndCalculate(fileName, &head, &result) == EXIT_SUCCESS) {
		printf("Result is: %0.5lf\n", result);
	}

	return EXIT_SUCCESS;
}

Position createNumber(double number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(numbers));
	if (!newElement)
	{
		printf("can't allocate memory\n");
		return NULL;
	}
	newElement->value = number;
	newElement->next = NULL;

	return newElement;
}

int insertNumberInList(Position head, Position newNumber)
{
	newNumber->next = head->next;
	head->next = newNumber;

	return EXIT_SUCCESS;
}

int calculate(char operation, double* result, Position head)
{
	double number1 = 0;
	double number2 = 0;
	number1 = head->next->value;
	number2 = head->next->next->value;

	switch (operation)
	{
	case '+':
		*result = number2 + number1;
		break;
	case '*':
		*result = number2 * number1;
		break;
	case '-':
		*result = number2 - number1;
		break;
	case '/':
		*result = number2 / number1;
		break;
	default:
		printf("can't read symbol");
		break;
	}

	return EXIT_SUCCESS;
}

int toDelete(Position head)
{
	Position current = NULL;
	current = (Position)malloc(sizeof(numbers));
	current = head->next;
	if (!current)
	{
		printf("empty list\n");
		return EXIT_FAILURE;
	}
	head->next = current->next;
	free(current);
	return EXIT_SUCCESS;
}

int readFileAndCalculate(char* fileName, Position head, double* result)
{
	char buffer[MAX_LENGTH] = { 0 };
	double number = 0;
	char operation = 0;
	Position newNumber = NULL;
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "r");
	if (!filePointer)
	{
		printf("can't open file\n");
		return EXIT_FAILURE;
	}
	int status = 0;
	fgets(buffer, MAX_LENGTH, filePointer);
	char* currentBuffer = buffer;
	int numBytes = 0;
	while (strlen(currentBuffer) > 0) {
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status != 1)
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			calculate(operation, result, head);
			toDelete(head);
			toDelete(head);
			number = *result;
		}
		newNumber = createNumber(number);
		if (!newNumber)
		{
			return EXIT_FAILURE;
		}
		insertNumberInList(head, newNumber);
		currentBuffer += numBytes;
	};
	fclose(filePointer);

	return EXIT_SUCCESS;
}



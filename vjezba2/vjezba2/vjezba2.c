#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int value;
	Position next;
} element;

int unosPocetak(Position head, int number);
int unosKraj(Position head, int number);
int ispisListe(Position head);
int brisiElement(Position head, int number);
int unosIza(Position head, int number, int insertNumber);
int unosPrije(Position head, int number, int insertNumber);
Position nadiPrethodni(Position head, int number);
int brisiMin(Position head);


int main()
{
	element head = { .value = 0,.next = NULL };
	unosPocetak(&head, 5);
	unosPocetak(&head, 15);
	unosPocetak(&head, 25);
	unosKraj(&head, 35);
	brisiElement(&head, 15);
	unosIza(&head, 5, 45);
	unosPrije(&head, 5, 55);
	brisiMin(&head);
	ispisListe(&head);

	return EXIT_SUCCESS;
}

int brisiMin(Position head)
{
	Position current = head->next;
	Position minimal = current;
	int min = current->value;
	while (current != NULL) {
		if (current->value < min)
		{
			min = current->value;
			minimal = current;
		}
		current = current->next;
	};
	
	Position prev = NULL;
	prev = (Position)malloc(sizeof(element));
	prev = nadiPrethodni(head, min);
	prev->next = minimal->next;
	free(minimal);


	return EXIT_SUCCESS;
}


int unosPrije(Position head, int number, int insertNumber)
{
	Position current = head->next;
	while (current != NULL) {
		if (current->value == number)
		{
			Position prev = nadiPrethodni(head, number);
			Position newElement = NULL;
			newElement = (Position)malloc(sizeof(element));
			newElement->value = insertNumber;
			newElement->next = prev->next;
			prev->next = newElement;
			return EXIT_SUCCESS;
		}
		current = current->next;
	};

	printf("%d is not in the list\n", number);
	return EXIT_SUCCESS;
}

Position nadiPrethodni(Position head, int number)
{
	Position current = head;
	while (current->next != NULL && current->next->value != number) {
		current = current->next;
	};
	if (current == NULL)
	{
		printf("%d is not in the list\n", number);
		return NULL;
	}
	return current;
}

int unosIza(Position head, int number, int insertNumber)
{
	Position current = head->next;
	while (current != NULL) {
		if (current->value == number)
		{
			Position newElement = NULL;
			newElement = (Position)malloc(sizeof(element));
			newElement->value = insertNumber;
			newElement->next = current->next;
			current->next = newElement;
			return EXIT_SUCCESS;
		}
		current = current->next;
	};

	printf("%d is not in the list\n", number);
	return EXIT_SUCCESS;
}

int brisiElement(Position head, int number)
{
	Position current = head;
	while (current->next != NULL) {
		if (current->next->value == number)
		{
			Position toDelete = current->next;
			current->next = current->next->next;
			free(toDelete);
			return EXIT_SUCCESS;
		}
		current = current->next;
	};

	printf("%d is not in list\n", number);
	return EXIT_SUCCESS;
}

int unosKraj(Position head, int number)
{
	Position current = head->next;
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(element));
	if (!newElement)
	{
		perror("can't allocate memory");
		return EXIT_FAILURE;
	}
	while (current->next != NULL) {
		//printf(" >%d< \n", current->value);
		current = current->next;
	};
	//printf(" >%d< \n", current->value);
	newElement->value = number;
	newElement->next = NULL;
	current->next = newElement;

	return EXIT_SUCCESS;
}

int unosPocetak(Position head, int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(element));
	if (!newElement)
	{
		printf("can't allocate memory");
		return EXIT_FAILURE;
	}
	newElement->value = number;
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}

int ispisListe(Position head)
{
	Position current = NULL;
	current = head->next;
	while (current != NULL) {
		printf("%d \n", current->value);
		current = current->next;
	};

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <stdlib.h>

struct _Cvor;
typedef struct _Cvor* Position;
typedef struct _Cvor {
	int element;
	Position next;
} cvor;

int unosp(Position head, int a);
int unosiza(Position head, int a, int b);
int brisi(Position head, int a);
int brisinaj(Position head);
void print(Position head);

int main()
{
	cvor head = { .element = 0,.next = NULL};
	unosp(&head, 4);
	unosp(&head, 3);
	unosp(&head, 2);
	unosp(&head, 1);
	unosiza(&head, 4, 5);
	brisi(&head, 5);
	brisinaj(&head);
	print(&head);

	return 0;
}

int brisinaj(Position head)
{
	Position current = head->next;
	Position prev = head;
	Position toDeletePrev = head;
	Position toDelete = head->next;
	int min = current->element;
	while (current != NULL)
	{
		if (current->element > min)
		{
			min = current->element;
			toDelete = current;
			toDeletePrev = prev;
		}
		current = current->next;
		prev = prev->next;
	}

	toDeletePrev->next = toDelete->next;
	free(toDelete);

	return 0;
}

int brisi(Position head, int a)
{
	Position current = head->next;
	Position prev = head;
	while (current != NULL)
	{
		if (current->element == a)
		{
			prev->next = current->next;
			free(current);
			return 0;
		}
		current = current->next;
		prev = prev->next;
	}
	printf("nema broja\n");
	return 0;

}


int unosiza(Position head, int a, int b)
{
	Position current = head->next;
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(cvor));
	newElement->element = b;
	while (current != NULL)
	{
		if (current->element == a)
		{
			newElement->next = current->next;
			current->next = newElement;
			return 0;
		}
		current = current->next;
	}
	return 0;
}


int unosp(Position head, int a)
{
	if (head->next == NULL)
	{
		Position newElement = NULL;
		newElement = (Position)malloc(sizeof(cvor));
		newElement->element = a;
		newElement->next = newElement;
		head->next = newElement;

	}
	return 0;
}

void print(Position head)
{
	Position current = head->next;
	while (current != NULL)
	{
		printf("%d ", current->element);
		current = current->next;
	}

}
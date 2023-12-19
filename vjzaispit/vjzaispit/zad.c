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

int prvi(Position head, int a);
int unos(Position head, int a, int b);
void print(Position head);
int brisi(Position head, int a);
Position prethodni(Position head, int a);
int najmanji(Position head);

int main()
{
	cvor head = { .element = 0,.next = NULL,.previous = NULL };
	prvi(&head, 5);
	prvi(&head, 45);
	prvi(&head, 15);
	prvi(&head, 25);
	unos(&head, 15, 35);
	brisi(&head, 15);
	brisi(&head, najmanji(&head));
	print(&head);

	return 0;
}


int najmanji(Position head)
{
	Position current = head->next;
	int min = current->element;
	while (current != NULL)
	{
		if (current->element < min)
		{
			min = current->element;
		}
		current = current->next;
	}

	return min;
}

Position prethodni(Position head, int a)
{
	Position pret = head;
	while (pret->next != NULL)
	{
		if (pret->next->element == a)
		{
			return pret;
		}
		pret = pret->next;
	}
	return NULL;
}

int brisi(Position head, int a)
{
	Position iter = head->next;
	while (iter != NULL)
	{
		if (iter->element == a)
		{
			Position current = prethodni(head, a)->next;
			Position pret = prethodni(head, a);
			if (current->next == NULL)
			{
				pret->next = NULL;
			}
			else
			{
				Position slj = current->next;
				pret->next = slj;
				slj->previous = pret;
			}
			free(current);
			return 0;
		}
		iter = iter->next;
	}
	printf("%d nije u listi\n", a);
	return 0;
}

int unos(Position head, int a, int b)
{
	Position current = head->next;
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(cvor));
	newElement->element = b;
	while (current != NULL)
	{
		if (current->element == a)
		{
			prvi(current, b);
			return 0;
		}
		current = current->next;
	}

	printf("\n%d nije u listi\n", a);
	return 0;
}

void print(Position head)
{
	Position current = head->next;
	while (current != NULL) {
		printf("%d ", current->element);
		current = current->next;
	};
}


int prvi(Position head, int a)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(cvor));
	newElement->element = a;
	newElement->next = head->next;
	head->next = newElement;
	newElement->previous = head;
	return 0;
}
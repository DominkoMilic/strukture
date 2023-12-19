#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <stdlib.h>

struct _Cvor;
typedef struct _Cvor* Position;
typedef struct _Cvor{
	int element;
	Position next;
	Position previous;
} cvor;

int unospd(Position head, int a);
void print(Position head);





int main()
{
	cvor head = { .element = 0,.next = NULL,.previous = NULL };
	unospd(&head, 1);
	unospd(&head, 2);
	unospd(&head, 3);
	unospd(&head, 4);
	print(&head);

	return 0;
}


int unospd(Position head, int a)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(cvor));
	newElement->element = a;
	newElement->next = head->next;
	newElement->previous = head;
	head->next = newElement;

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

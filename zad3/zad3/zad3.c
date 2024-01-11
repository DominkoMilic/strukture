#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define NO_PERSON_FOUND (NULL)
#define EMPTY_LIST (-1)
#define NO_PERSON_FOUND_INT (-2)
#define SINGLE_PERSON_IN_LIST (-3)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;

Position createPerson();
Position findLast(Position head);
char* enterSurname();
int printPerson(Position person);
Position findPrevious(Position head);
int insertAtFrontOfTheList(Position head);
int insertAtEndOfTheList(Position head);
int printList(Position firstItem);
Position findPerson(Position firstItem);
int deletePerson(Position head);
int insertAfterPerson(Position person);


int main(int argc, char** argv)
{
	Person Head = { .next = NULL,.name = {0},.surname = {0},.birthYear = 0 };

	insertAtFrontOfTheList(&Head);
	insertAtFrontOfTheList(&Head);
	insertAtEndOfTheList(&Head);
	insertAtEndOfTheList(&Head);
	findPerson(&Head);
	deletePerson(&Head);
	printList(&Head);

	return EXIT_SUCCESS;
}

int insertAtFrontOfTheList(Position head)
{
	Position newPerson = NULL;
	newPerson = createPerson();
	if (newPerson) 
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

Position findPrevious(Position head)
{
	Position current = head;
	char surname[MAX_LENGTH] = { 0 };
	strcpy(surname, enterSurname());
	if (!head->next)
	{
		printf("empty list\n");
		return NO_PERSON_FOUND;
	}

	do
	{
		if (strcmp(surname, current->next->surname) == 0)
		{
			return current;
		}
		else
		{
			current = current->next;
		}
	} while (current->next != NULL);

	return current;
}


Position findLast(Position Head)
{
	Position current = Head;
	while (current->next)
	{
		current = current->next;
	}
	return current;
}

int insertAtEndOfTheList(Position head)
{
	Position newPerson = NULL;
	newPerson = createPerson();
	Position last = NULL;
	if (newPerson)
	{
		last = findLast(head);
		newPerson->next = last->next;
		last->next = newPerson;
	}


	return EXIT_SUCCESS;
}

int insertAfterPerson(Position person)
{
	Position newPerson = NULL;
	newPerson = createPerson();
	if (newPerson)
	{
		newPerson->next = person->next;
		person->next = newPerson;
	}
	return EXIT_SUCCESS;
}

Position createPerson()
{
	Position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int birthYear = 0;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		printf("Can't allocate memory");
		return NULL;
	}
	printf("Enter name: ");
	scanf(" %s", name);
	printf("Enter surname: ");
	scanf(" %s", surname);
	printf("Enter birth year: ");
	scanf(" %d", &birthYear);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear, birthYear;


	return newPerson;
}


int printList(Position first)
{
	Position current = first;
	if (!first)
	{
		printf("empty list\n");
	}
	while (current)
	{
		printPerson(current);
		current = current->next;
	}

	return EXIT_SUCCESS;
}

int printPerson(Position person)
{
	printf("name: %s\nsurname: %s\nbirth year: %d\n", person->name, person->surname, person->birthYear);
	return EXIT_SUCCESS;
}

char* enterSurname()
{
	char surname[MAX_LENGTH] = { 0 };
	printf("enter surname: ");
	scanf(" %s", surname);
	return surname;
}

Position findPerson(Position head)
{
	Position current = head;
	char surname[MAX_LENGTH] = { 0 };
	if (!head)
	{
		printf("Empty list\n");
		return NO_PERSON_FOUND;
	}
	strcpy(surname, enterSurname());
	do {
		if (strcmp(surname, current->surname) == 0)
		{
			return current;
		}
		else
		{
			current = current->next;
		}
	
	} while (current != NULL);

	return NO_PERSON_FOUND;
}

int deletePerson(Position head)
{
	Position current = NULL;
	char surname[MAX_LENGTH] = { 0 };
	strcpy(surname, enterSurname());
	if (head->next)
	{
		Position previous = NULL;
		while (current->next && strcmp(current->surname, surname) != 0)
		{
			previous = current;
			current = current->next;
		}
		if (previous && previous->next && (current->surname, surname) == 0)
		{
			printPerson(current);
			previous->next = current->next;
			free(current);
		}
		else
		{
			return NO_PERSON_FOUND;
		}
	}
	else
	{
		return EMPTY_LIST;
	}
		return EXIT_SUCCESS;
}




#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 20

struct Person;
typedef struct Person* position;
typedef struct Person
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthyear;
	position next;
}person;

int AddToFront(position head);
int InsertAfter(position selected, position new);
position CreatePerson();
int PrintList(position head);
int AddToEnd(position head);
position FindSurname(position head, char* surname);
int Delete(position head, position selected);
int AddAfter(position head, char* selected);
int AddBefore(position head, char* selected);
int Sort(position head);
int SwapItems(position first, position second);
int WriteFile(position head, FILE *f);
int ReadFile(position head, FILE *u);

int main(void)
{
	person Head = { .next = NULL,.name = {0}, .surname = {0}, .birthyear = 0 };

	FILE *f = NULL;
	FILE *u = NULL;

	f = fopen("studenti", "w");
	u = fopen("unos.txt", "r");
	if (u == NULL || f == NULL)
		return 0;
	Head.next = NULL;

	AddToFront(&Head);
	AddToEnd(&Head);
	/*printf("which surname you want to delete: ");
	char* toDelete[MAX_LENGTH] = { 0 };
	scanf(" %s", toDelete);
	Delete(&Head, FindSurname(&Head, toDelete));*/
	//AddAfter(&Head, "milic");
	AddBefore(&Head, "milic");
	
	Sort(&Head);

	PrintList(&Head);

	WriteFile(Head.next, f);
	ReadFile(Head.next, u);


	fclose(f);
	fclose(u);

	return 0;
}

position CreatePerson() {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		printf("couldn't allocate memory");
		return NULL;
	}
	char newname[MAX_LENGTH] = { 0 };
	char newsurname[MAX_LENGTH] = { 0 };
	int newbirthyear = 0;
	printf("Enter name: ");
	scanf(" %s", newname);
	strcpy(newPerson->name, newname);
	printf("Enter surname: ");
	scanf(" %s", newsurname);
	strcpy(newPerson->surname, newsurname);
	printf("Enter birthyear: ");
	scanf(" %d", &newbirthyear);
	newPerson->birthyear = newbirthyear;

	return newPerson;
}

int AddToFront(position head) {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		printf("couldn't allocate memory");
		return EXIT_FAILURE;
	}
	newPerson = CreatePerson();
	if (!newPerson)
	{
		printf("couldn't create a new person");
		return EXIT_FAILURE;
	}
	InsertAfter(head, newPerson);
	
	return EXIT_SUCCESS;
}

int InsertAfter(position selected, position new)
{
	new->next = selected->next;
	selected->next = new;

	return EXIT_SUCCESS;
}

int PrintList(position head)
{
	position temp = head;
	int counter = 0;
	printf("Person list:\n");
	while (temp->next)
	{
		temp = temp->next;
		printf("name: %s, surname: %s, birthyear: %d\n", temp->name, temp->surname, temp->birthyear);
		counter++;
	}
	if (counter == 0)
		printf("List is empty\n");

	return EXIT_SUCCESS;
}

int AddToEnd(position head)
{
	position newPerson = NULL;
	position last = head;
	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		perror("couldn't allocate memory\n");
		return EXIT_FAILURE;
	}
	newPerson = CreatePerson();
	if (!newPerson)
		return EXIT_FAILURE;
	while (last->next != NULL)
		last = last->next;
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

position FindSurname(position head, char* surname)
{
	position temp = head;
	while (temp != NULL)
	{
		if (strcmp(surname, temp->surname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	printf("couldn't find surname in list\n");

	return NULL;
}

int Delete(position head, position selected)
{
	position temp = selected;
	if (temp == NULL)
	{
		printf("wrong argument\n");
		return EXIT_FAILURE;
	}
	while (head != NULL)
	{
		if (head->next == temp)
		{
			head->next = temp->next;
			free(selected);
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int AddAfter(position head, char* selected)
{
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		printf("couldn't allocate memory");
		return EXIT_FAILURE;
	}
	newPerson = CreatePerson();
	if (!newPerson)
		return EXIT_FAILURE;
	while (head->next != NULL)
	{
		if (strcmp(head->surname, selected) == 0)
		{
			newPerson->next = head->next;
			head->next = newPerson;
			break;
		}
		head = head->next;
	}

	return EXIT_SUCCESS;
}

int AddBefore(position head, char* selected)
{
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		printf("couldn't allocate memory");
		return EXIT_FAILURE;
	}
	newPerson = CreatePerson();
	if (!newPerson)
		return EXIT_FAILURE;
	while (head != NULL)
	{
		if (strcmp(head->next->surname, selected) == 0)
		{
			newPerson->next = head->next;
			head->next = newPerson;
			break;
		}
		head = head->next;
	}

	return EXIT_SUCCESS;
}

int Sort(position head) {
	int swapped = 0;
	position lastPersonRead = NULL;
	position start = head;

	if (!start) {
		printf("Empty list!\n");
		return EXIT_FAILURE;
	}
	else if (!head->next) {
		printf("Only single element in list!\n");
		return EXIT_SUCCESS;
	}

	do {
		swapped = 0;
		position current = start;

		while (current->next != lastPersonRead) {
			if (strcmp(current->surname, current->next->surname) > 0) {
				SwapItems(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		lastPersonRead = current;
	} while (swapped);

	return EXIT_SUCCESS;
}

int SwapItems(position first, position second) {
	char tempName[MAX_LENGTH];
	char tempSurname[MAX_LENGTH];
	int tempBirthYear;

	strcpy(tempName, first->name);
	strcpy(tempSurname, first->surname);
	tempBirthYear = first->birthyear;

	strcpy(first->name, second->name);
	strcpy(first->surname, second->surname);
	first->birthyear = second->birthyear;

	strcpy(second->name, tempName);
	strcpy(second->surname, tempSurname);
	second->birthyear = tempBirthYear;

	return EXIT_SUCCESS;
}

int WriteFile(position head, FILE *f)
{
	while (head != NULL)
	{
		fprintf(f, "Name: %s, Surname: %s, Birthyear: %d\n", head->name, head->surname, head->birthyear);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int ReadFile(position head, FILE *f)
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthyear;

	while (!feof(f))
	{
		fscanf(f, "%s %s %d", name, surname, &birthyear);
		pocetak(head, name, surname, birthyear);
	}
	return EXIT_SUCCESS;
}
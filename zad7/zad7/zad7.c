#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct _directory;
typedef struct _directory* PositionDirectory;
typedef struct _directory
{
	char name[50];
	PositionDirectory sibling;
	PositionDirectory child;
} directory;

struct _stack;
typedef struct _stack* PositionLevelStack;
typedef struct _stack
{
	PositionDirectory el;
	PositionLevelStack next;
} stack;

int Print(PositionLevelStack p);
int md(char* ime, PositionDirectory p);
PositionDirectory cd(char* ime, PositionDirectory p);
int dir(PositionDirectory p);
int pushStog(PositionDirectory p, PositionLevelStack s);
PositionLevelStack popStog(PositionLevelStack p);
int DeleteAll(PositionDirectory p);

int main()
{
	directory head = { .name = "C",.sibling = NULL,.child = NULL };
	PositionLevelStack current = NULL;
	PositionDirectory currentDir = NULL;
	PositionDirectory check = NULL;
	PositionLevelStack swap = NULL;
	char command[20];
	char newName[50];

	currentDir = &head;
	current = (PositionLevelStack)malloc(sizeof(stack));
	if (current == NULL)
	{
		perror("couldn't allocate memory\n");
		return EXIT_FAILURE;
	}
	current->el = &head;
	current->next = NULL;

	while (1)
	{
		Print(current);
		scanf("%s", command);
		if (strcmp(command, "exit") == 0)
		{
			DeleteAll(head.child);
			break;
		}
		else if (strcmp(command, "md") == 0)
		{
			scanf("%s", newName);
			md(newName, currentDir);
		}
		else if (strcmp(command, "cd") == 0)
		{
			scanf("%s", newName);
			check = currentDir;
			currentDir = cd(newName, currentDir);
			if (check != currentDir)
				pushStog(currentDir, current);
		}
		else if (strcmp(command, "dir") == 0)
		{
			dir(currentDir);
		}
		else if (strcmp(command, "cd..") == 0)
		{
			if (currentDir == &head)
				continue;
			swap = popStog(current);
			currentDir = swap->el;
		}
		else
		{
			printf("that is not a command\n");
		}
	}



	return 0;
}

int Print(PositionLevelStack p)
{
	while (p != NULL)
	{
		printf("%s:", p->el->name);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int md(char* ime, PositionDirectory p)
{
	PositionDirectory q = NULL;
	q = (PositionDirectory)malloc(sizeof(directory));
	if (q == NULL)
	{
		perror("couldn't allocate memory\n");
		return EXIT_FAILURE;
	}
	strcpy(q->name, ime);
	q->child = NULL;
	q->sibling = NULL;

	if (p->child == NULL)
	{
		p->child = q;
		return EXIT_SUCCESS;
	}

	p = p->child;
	while (p != NULL)
	{
		if (strcmp(ime, p->name) == 0)
		{
			printf("directory with that name already exist\n");
			return EXIT_SUCCESS;
		}
		if (p->sibling == NULL)
		{
			p->sibling = q;
			break;
		}
		p = p->sibling;
	}
	return EXIT_SUCCESS;
}

PositionDirectory cd(char* ime, PositionDirectory p)
{
	PositionDirectory q = p;
	p = p->child;
	while (p != NULL)
	{
		if (strcmp(p->name, ime) == 0)
			return p;
		p = p->sibling;
	}
	if (p == NULL)
	{
		printf("that directory doesn't exist\n");
		return q;
	}
}

int dir(PositionDirectory p)
{
	p = p->child;
	if (p == NULL)
	{
		printf("there is no any directory\n");
		return EXIT_SUCCESS;
	}
	while (p != NULL)
	{
		printf("\t%s\n", p->name);
		p = p->sibling;
	}
	return EXIT_SUCCESS;
}

int pushStog(PositionDirectory p, PositionLevelStack s)
{
	PositionLevelStack q = NULL;
	q = (PositionLevelStack)malloc(sizeof(stack));
	if (q == NULL)
	{
		perror("couldn't allocate memory\n");
		return EXIT_FAILURE;
	}
	q->el = p;

	while (s->next != NULL)
		s = s->next;
	q->next = s->next;
	s->next = q;
	return EXIT_SUCCESS;
}

PositionLevelStack popStog(PositionLevelStack p)
{
	PositionLevelStack prev = p;
	PositionLevelStack t = NULL;
	while (p->next != NULL)
	{
		prev = p;
		p = p->next;
	}
	t = p;
	prev->next = NULL;
	free(t);
	return prev;
}

int DeleteAll(PositionDirectory p)
{
	if (p == NULL)
		return EXIT_SUCCESS;
	DeleteAll(p->sibling);
	DeleteAll(p->child);
	free(p);
	return EXIT_SUCCESS;
}

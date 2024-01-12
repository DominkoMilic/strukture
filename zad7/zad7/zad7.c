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
	PositionDirectory element;
	PositionLevelStack next;
} stack;

int Print(PositionLevelStack currentDirectory);
int md(char* ime, PositionDirectory currentDirectory);
PositionDirectory cd(char* ime, PositionDirectory currentDirectory);
int dir(PositionDirectory currentDirectory);
int pushStog(PositionDirectory currentDirectory, PositionLevelStack headLevelStack);
PositionLevelStack popStog(PositionLevelStack headLevelStack);
int DeleteAll(PositionDirectory currentDirectory);

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
	current->element = &head;
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
			currentDir = swap->element;
		}
		else
		{
			printf("that is not a command\n");
		}
	}



	return 0;
}

int Print(PositionLevelStack headLevelStack)
{
	while (headLevelStack != NULL)
	{
		printf("%s:", headLevelStack->element->name);
		headLevelStack = headLevelStack->next;
	}
	return EXIT_SUCCESS;
}

int md(char* ime, PositionDirectory currentDirectory)
{
	PositionDirectory newElement = NULL;
	newElement = (PositionDirectory)malloc(sizeof(directory));
	if (newElement == NULL)
	{
		perror("couldn't allocate memory\n");
		return EXIT_FAILURE;
	}
	strcpy(newElement->name, ime);
	newElement->child = NULL;
	newElement->sibling = NULL;

	if (currentDirectory->child == NULL)
	{
		currentDirectory->child = newElement;
		return EXIT_SUCCESS;
	}

	currentDirectory = currentDirectory->child;
	while (currentDirectory != NULL)
	{
		if (strcmp(ime, currentDirectory->name) == 0)
		{
			printf("directory with that name already exist\n");
			return EXIT_SUCCESS;
		}
		if (currentDirectory->sibling == NULL)
		{
			currentDirectory->sibling = newElement;
			break;
		}
		currentDirectory = currentDirectory->sibling;
	}
	return EXIT_SUCCESS;
}

PositionDirectory cd(char* ime, PositionDirectory currentDirectory)
{
	PositionDirectory temp = currentDirectory;
	currentDirectory = currentDirectory->child;
	while (currentDirectory != NULL)
	{
		if (strcmp(currentDirectory->name, ime) == 0)
			return currentDirectory;
		currentDirectory = currentDirectory->sibling;
	}
	if (currentDirectory == NULL)
	{
		printf("that directory doesn't exist\n");
		return temp;
	}
}

int dir(PositionDirectory currentDirectory)
{
	currentDirectory = currentDirectory->child;
	if (currentDirectory == NULL)
	{
		printf("there is no any directory\n");
		return EXIT_SUCCESS;
	}
	while (currentDirectory != NULL)
	{
		printf("\t%s\n", currentDirectory->name);
		currentDirectory = currentDirectory->sibling;
	}
	return EXIT_SUCCESS;
}

int pushStog(PositionDirectory currentDirectory, PositionLevelStack headLevelStack)
{
	PositionLevelStack newElement = NULL;
	newElement = (PositionLevelStack)malloc(sizeof(stack));
	if (newElement == NULL)
	{
		perror("couldn't allocate memory\n");
		return EXIT_FAILURE;
	}
	newElement->element = currentDirectory;

	while (headLevelStack->next != NULL)
		headLevelStack = headLevelStack->next;
	newElement->next = headLevelStack->next;
	headLevelStack->next = newElement;
	return EXIT_SUCCESS;
}

PositionLevelStack popStog(PositionLevelStack currentDirectory)
{
	PositionLevelStack prev = currentDirectory;
	PositionLevelStack temp = NULL;
	while (currentDirectory->next != NULL)
	{
		prev = currentDirectory;
		currentDirectory = currentDirectory->next;
	}
	temp = currentDirectory;
	prev->next = NULL;
	free(temp);
	return prev;
}

int DeleteAll(PositionDirectory currentDirectory)
{
	if (currentDirectory == NULL)
		return EXIT_SUCCESS;
	DeleteAll(currentDirectory->sibling);
	DeleteAll(currentDirectory->child);
	free(currentDirectory);
	return EXIT_SUCCESS;
}

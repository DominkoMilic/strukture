#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


struct Node;
typedef struct Node* position;
typedef struct Node
{
	int value;
	position left;
	position right;
}node;

position Insert(position root, int x);
void WriteInFile(position root, FILE* file);
int Replace(position root);
void FreeMemory(position root);
int Random();


int main(void)
{
	FILE* file = fopen("stablo", "w");;
	position root = NULL;
	position rootRand = NULL;
	srand((unsigned int)time(NULL));
	int a[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int i;

	for (i = 0; i < 10; i++) {
		root = Insert(root, a[i]);
	}
	for (i = 0; i < 10; i++) {
		rootRand = Insert(rootRand, Random());
	}
	
	WriteInFile(root, file);
	fprintf(file, "\n");
	Replace(root);
	WriteInFile(root, file);
	fprintf(file, "\n\n");

	WriteInFile(rootRand, file);
	fprintf(file, "\n");
	Replace(rootRand);
	WriteInFile(rootRand, file);

	fclose(file);

	FreeMemory(root);
	FreeMemory(rootRand);

	return 0;
}

position Insert(position root, int x)
{
	position newElement = NULL;
	if (root == NULL)
	{
		newElement = (position)malloc(sizeof(node));
		newElement->value = x;
		newElement->left = NULL;
		newElement->right = NULL;
		return newElement;
	}
	if (x >= root->value)
		root->right = Insert(root->right, x);
	if (x < root->value)
		root->left = Insert(root->left, x);

	return root;
}

void WriteInFile(position root, FILE* file)
{
	if (root == NULL)
		return;
	WriteInFile(root->right, file);
	fprintf(file, "%d ", root->value);
	WriteInFile(root->left, file);
}

int Replace(position root) {
		if (root == NULL)
			return 0;
		int temp = root->value;
		root->value = Replace(root->left) + Replace(root->right);
		return temp + root->value;
}

void FreeMemory(position root)
{
	if (!root)
		return;
	FreeMemory(root->left);
	FreeMemory(root->right);
	free(root);
}

int Random() {
	return rand() % 81 + 10;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct _node;
typedef struct _node* Position;
typedef struct _node {
	int value;
	Position left;
	Position right;
} Node;


Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int orderLevel(Position root);

int main() {
	Position root = NULL;
	root = insert(root, 2);
	insert(root, 5);
	insert(root, 7);
	insert(root, 8);
	insert(root, 11);
	insert(root, 1);
	insert(root, 4);
	insert(root, 2);
	insert(root, 3);
	insert(root, 7);

	printf("inorder: ");
	inorder(root);
	printf("\n");

	printf("preorder: ");
	preorder(root);
	printf("\n");

	printf("postorder: ");
	postorder(root);
	printf("\n");

	printf("level order: ");
	orderLevel(root);
	printf("\n");


	return EXIT_SUCCESS;
}

Position createNode(int value)
{
	Position newNode = NULL;
	newNode = (Position)malloc(sizeof(Node));
	if (!newNode)
	{
		printf("couldn't allocate memory\n");
		return NULL;
	}
	newNode->value = value;
	newNode->right = NULL;
	newNode->left = NULL;
	return newNode;
}

Position insert(Position root, int value) {
	if (root == NULL)
		return createNode(value);

	if (value < root->value)
		root->left = insert(root->left, value);
	else if (value >= root->value)
		root->right = insert(root->right, value);

	return root;
}

int inorder(Position root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}

	return EXIT_SUCCESS;
}

int preorder(Position root) {
	if (root) {
		printf("%d ", root->value);
		preorder(root->left);
		preorder(root->right);
	}

	return EXIT_SUCCESS;
}


int postorder(Position root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->value);
	}

	return EXIT_SUCCESS;
}

int orderLevel(Position root) {
	if (root == NULL)
		return EXIT_SUCCESS;

	Position queue[100] = { 0 };
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear) {
		Position current = queue[front++];

		printf("%d ", current->value);

		if (current->left != NULL)
			queue[rear++] = current->left;

		if (current->right != NULL)
			queue[rear++] = current->right;
	}

	return EXIT_SUCCESS;
}

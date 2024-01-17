#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_LENGTH (1024)


struct User;
typedef struct User* userPosition;
typedef struct User {
	char name[MAX_LENGTH];
	int booksNumber;
	userPosition next;
} user;

//naslov, autor, godina izdanja i dostupni primjerci
struct Book;
typedef struct Book* bookPosition;
typedef struct Book {
	char title[MAX_LENGTH];
	char author[MAX_LENGTH];
	int releaseYear;
	int available;
	bookPosition next;
	userPosition userHead;
} book;

bookPosition CreateNewBook(char* title, char* author, int releaseYear, int available);
void AllBooksSorted(bookPosition bookHead, char* title, char* author, int releaseYear, int available);
void ListPrint(bookPosition bookHead);
void Menu(bookPosition bookHead, char* fileName);
void SearchByYear(bookPosition bookHead, int searchYear);
void SearchByAuthor(bookPosition bookHead, char* author);
userPosition CreateNewUser(char* name, int numberOfBooks);
int AllUsersSorted(bookPosition bookHead, char* name, int numberOfBooks);
void InsertUserToBook(bookPosition bookHead, char* userName, char* title, int numberOfBooks);
int ReadFromFile(char* fileName, bookPosition bookHead);
int WriteToFile(char* fileName, bookPosition bookHead);
bool CheckIfUserExist(bookPosition bookHead, char* name);
bool CheckIfBookExist(bookPosition bookHead, char* name);
int CheckingUserNumberOfBook(bookPosition bookHead, char* name);
int CheckingAvailableNumberOfBook(bookPosition bookHead, char* title);
void PrintUsers(bookPosition bookHead);
int ReadingUsers(char* fileName, bookPosition bookHead, char* title);
int CheckingUserNumberOfCertainBook(bookPosition bookHead, char* title, char* userName);
int BookReturn(bookPosition bookHead, char* userName, char* title, int returnNumber);
int FreeMemory(userPosition currentUser, userPosition previousUser);

int main() {

	book bookHead = {
		 .title = {0},
		 .author = {0},
		 .releaseYear = 0,
		 .available = 0,
		 .next = NULL,
		 .userHead = NULL,
	};
	

	char* fileName = "library.txt";
	ReadFromFile(fileName, &bookHead);
	

	Menu(&bookHead, fileName);

	return 0;
}

void Menu(bookPosition bookHead, char* fileName) {
	printf("press:\na for alphabetical print of books\nb for alphabetical print of users\nc for searching books by release year\nd for searching books by author\ne for entering new user\nf for loaning the book\ng for returning the book\nh for saving current information in file\nx for exit\n");
	char choice = ' ';
	scanf(" %c", &choice);
	switch (choice)
	{
		case 'a': {
			ListPrint(bookHead);
			break;
		}
		case 'b': {

			break;
		}
		case 'c': {
			int searchYear = 0;
			printf("Enter year: \n");
			scanf("%d", &searchYear);
			SearchByYear(bookHead, searchYear);
			break;
		}
		case 'd': {
			char author[MAX_LENGTH] = { 0 };
			printf("Enter author: \n");
			scanf(" ");
			fgets(author, sizeof(author), stdin);
			author[strcspn(author, "\n")] = '\0'; //removing new line from author
			SearchByAuthor(bookHead, author);
			break;
		}
		case 'e': {
			char name[MAX_LENGTH] = { 0 };
			printf("Enter new user: \n");
			scanf(" ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0'; //removing new line from name
			if (CheckIfUserExist(bookHead, name) == true)
				printf("%s is already a user\n", name);
			else
				AllUsersSorted(bookHead, name, 0);
			break;
		}
		case 'f': {
			char name[MAX_LENGTH] = { 0 };
			printf("Enter users name: \n");
			scanf(" ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0'; //removing new line from name
			if (CheckIfUserExist(bookHead, name) == false) {
				printf("Sorry, but that person is not one of our users\n");
				break;
			}
			if (CheckingUserNumberOfBook(bookHead, name) == 5) {
				printf("Sorry, but you cannot loan more than 5 books at the same time\n");
				break;
			}
			printf("Enter the name of the book you want to loan: \n");
			char title[MAX_LENGTH] = { 0 };
			scanf(" ");
			fgets(title, sizeof(title), stdin);
			title[strcspn(title, "\n")] = '\0'; //removing new line from name
			if (CheckIfBookExist(bookHead, title) == false) {
				printf("Sorry, but we don't have that book\n");
				break;
			}
			printf("Enter the number of books you want to loan: \n");
			int loanNumber = 0;
			scanf("%d", &loanNumber);
			int currentUserNumberOfBooks = CheckingUserNumberOfBook(bookHead, name);
			int currentlyAvailable = CheckingAvailableNumberOfBook(bookHead, title);
			if (currentUserNumberOfBooks + loanNumber > 5) {
				printf("Sorry, but you cannot loan more than 5 books, you can loan %d more books\n", 5 - currentUserNumberOfBooks);
				break;
			}
			else if (currentlyAvailable < loanNumber) {
				printf("Sorry, but we only have %d of that book remaining, do you want to loan %d books?(yes/no)\n", currentlyAvailable, currentlyAvailable);
				char answer[10] = { 0 };
				scanf(" %s", answer);
				if (strcmp(answer, "yes") == 0)
				{
					InsertUserToBook(bookHead, name, title, currentlyAvailable);
					break;
				}
				else
					break;
			}
			InsertUserToBook(bookHead, name, title, loanNumber);
			break;
		}
		case 'g': {
			char name[MAX_LENGTH] = { 0 };
			printf("Enter users name: \n");
			scanf(" ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0'; //removing new line from name
			if (CheckIfUserExist(bookHead, name) == false) {
				printf("Sorry, but that person is not one of our users\n");
				break;
			}
			printf("Enter the name of the book you want to return: \n");
			char title[MAX_LENGTH] = { 0 };
			scanf(" ");
			fgets(title, sizeof(title), stdin);
			title[strcspn(title, "\n")] = '\0'; //removing new line from name
			if (CheckIfBookExist(bookHead, title) == false) {
				printf("Sorry, but we don't have that book\n");
				break;
			}
			printf("Enter the number of books you want to return: \n");
			int returnNumber = 0;
			scanf("%d", &returnNumber);
			int numberOfUserCertainBook = CheckingUserNumberOfCertainBook(bookHead, title, name);
			if (returnNumber > numberOfUserCertainBook) {
				printf("Sorry, but user %s don't have %d books titled %s\n", name, returnNumber, title);
			}
			else {
				BookReturn(bookHead, name, title, returnNumber);
			}

			break;
		}
		case 'h': {
			printf("Saving to file ""library.txt");
			WriteToFile(fileName, bookHead);
			break;
		}
		case 'x': {
			printf("exiting");
			return;
		}
	}
	Menu(bookHead, fileName);
}

userPosition CreateNewUser(char* name, int numberOfBooks) {
	userPosition newUser = NULL;
	newUser = (userPosition)malloc(sizeof(user));
	if (!newUser) {
		printf("couldn't allocate memory");
		return NULL;
	}

	strcpy(newUser->name, name);
	newUser->booksNumber = numberOfBooks;
	newUser->next = NULL;

	return newUser;
}

bookPosition CreateNewBook(char* title, char* author, int releaseYear, int available) {
	bookPosition newElement = NULL;
	newElement = (bookPosition)malloc(sizeof(book));
	if (!newElement) {
		printf("couldn't allocate memory");
		return NULL;
	}

	strcpy(newElement->title, title);
	strcpy(newElement->author, author);
	newElement->releaseYear = releaseYear;
	newElement->available = available;
	newElement->userHead = NULL;
	newElement->next = NULL;

	return newElement;
}


int AllUsersSorted(bookPosition bookHead, char* name, int numberOfBooks) {
	userPosition newElement = CreateNewUser(name, numberOfBooks);

	if (!newElement) {
		printf("couldn't allocate memory");
		return EXIT_FAILURE;
	}

	userPosition current = bookHead->userHead;
	userPosition prev = NULL;

	while (current != NULL) {
		int compareResult = strcmp(name, current->name);
		if (compareResult == 0) {
			current->booksNumber = (current->booksNumber) + numberOfBooks;
			free(newElement);
			return EXIT_SUCCESS;
		}
		else if (compareResult < 0) {
			newElement->next = current;
			if (prev == NULL) {
				bookHead->userHead = newElement;
			}
			else {
				prev->next = newElement;
			}
			return EXIT_SUCCESS;
		}

		prev = current;
		current = current->next;
	}

	if (prev == NULL) {
		newElement->next = NULL;
		bookHead->userHead = newElement;
	}
	else {
		newElement->next = NULL;
		prev->next = newElement;
	}
	return EXIT_SUCCESS;
}

void AllBooksSorted(bookPosition bookHead, char* title, char* author, int releaseYear, int available) {
	bookPosition newElement = CreateNewBook(title, author, releaseYear, available);
	bookPosition current = bookHead;
	bookPosition previous = NULL;

	while (current != NULL) {
		int comparisonResult = strcmp(current->title, title);

		if (comparisonResult > 0) {
			break;
		}
		else if (comparisonResult == 0) {
			break;
		}

		previous = current;
		current = current->next;
	}

	if (previous == NULL) {
		newElement->next = bookHead;
		bookHead = newElement;
	}
	else {
		previous->next = newElement;
		newElement->next = current;
	}

}

void PrintUsers(bookPosition bookHead) {
	printf("svi useri:\n");
	userPosition currentUser = bookHead->userHead;
	while (currentUser != NULL) {
		printf("%s %d\n", currentUser->name, currentUser->booksNumber);
		currentUser = currentUser->next;
	}
}

void ListPrint(bookPosition bookHead) {
	bookPosition currentBook = bookHead->next;
	userPosition currentUser = NULL;
	while (currentBook != NULL) {
		printf("TITLE: %s\n", currentBook->title);
		printf("AUTHOR: %s\n", currentBook->author);
		printf("RELEASE YEAR: %d.\n", currentBook->releaseYear);
		printf("AVAILABLE: %d\n", currentBook->available);
		printf("USERS: \n");
		currentUser = currentBook->userHead;
		while (currentUser != NULL) {
			printf("%s\n", currentUser->name);
			currentUser = currentUser->next;
		}
		printf("\n");
		currentBook = currentBook->next;
	}

	PrintUsers(bookHead);
}


void SearchByYear(bookPosition bookHead, int searchYear) {
	bookPosition current = bookHead->next;
	int counter = 0;
	while (current != NULL) {
		if (current->releaseYear == searchYear) {
			counter++;
			printf("TITLE: %s\n", current->title);
			//printf("AUTHOR: %s\n", current->author);
			//printf("RELEASE YEAR: %d.\n", current->releaseYear);
			printf("AVAILABLE: %d\n\n", current->available);
		}
		current = current->next;
	}
	if (counter == 0)
		printf("Sorry, we don't have any book from that year\n");
}

void SearchByAuthor(bookPosition bookHead, char* author) {
	bookPosition current = bookHead->next;
	int counter = 0;
	printf("\n");
	while (current != NULL) {
		if (strcmp(current->author, author) == 0) {
			counter++;
			printf("TITLE: %s\n", current->title);
			//printf("AUTHOR: %s\n", current->author);
			//printf("RELEASE YEAR: %d.\n", current->releaseYear);
			printf("AVAILABLE: %d\n\n", current->available);
		}
		current = current->next;
	}
	if (counter == 0)
		printf("Sorry, we don't have any book from that author\n");
}


int ReadFromFile(char* fileName, bookPosition bookHead) {
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "r");
	if (filePointer == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	char author[MAX_LENGTH] = { 0 }, title[MAX_LENGTH] = { 0 };
	int releaseYear = 0;
	int available = 0;
	char bookID[MAX_LENGTH] = { 0 }, IDFile[MAX_LENGTH] = { 0 };
	bookPosition currentBook = bookHead;

	while (fscanf(filePointer, "TITLE: %1023[^\n]\n", title) == 1) {
		fscanf(filePointer, "AUTHOR: %1023[^\n]\n", author);
		fscanf(filePointer, "RELEASE YEAR: %d\n", &releaseYear);
		fscanf(filePointer, "AVAILABLE: %d\n", &available);
		fscanf(filePointer, "USERS: %1023[^\n]\n", bookID);
		strcpy(IDFile, bookID);
		strcat(IDFile, ".txt");
		AllBooksSorted(bookHead, title, author, releaseYear, available);
		ReadingUsers(IDFile, bookHead, title);
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}


void InsertUserToBook(bookPosition bookHead, char* userName, char* title, int numberOfBooks) {
	AllUsersSorted(bookHead, userName, numberOfBooks);
	int newNumberOfBooks = numberOfBooks + CheckingUserNumberOfBook(bookHead, userName);
	userPosition newUser = CreateNewUser(userName, newNumberOfBooks);
	bookPosition currentBook = bookHead->next;
	while (currentBook != NULL) {
		if (strcmp(currentBook->title, title) == 0) {
			currentBook->available = currentBook->available - numberOfBooks;
			if (currentBook->userHead == NULL)
			{
				currentBook->userHead = newUser;
				newUser->next = NULL;
			}
			else {
				newUser->next = currentBook->userHead;
				currentBook->userHead = newUser;
			}
		}
		currentBook = currentBook->next;
	}

}


bool CheckIfUserExist(bookPosition bookHead, char* name) {
	userPosition first = bookHead->userHead;
	while (first != NULL) {
		if (strcmp(first->name, name) == 0)
			return true;
		first = first->next;
	}

	return false;
}

bool CheckIfBookExist(bookPosition bookHead, char* name) {
	bookPosition current = bookHead->next;
	while (current != NULL) {
		if (strcmp(current->title, name) == 0)
			return true;
		current = current->next;
	}

	return false;
}

int CheckingUserNumberOfBook(bookPosition bookHead, char* name) {
	userPosition current = bookHead->userHead;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current->booksNumber;
		}
		current = current->next;
	}

	return -1;
}

int CheckingAvailableNumberOfBook(bookPosition bookHead, char* title) {
	bookPosition current = bookHead->next;
	while (current != NULL) {
		if (strcmp(current->title, title) == 0) {
			return current->available;
		}
		current = current->next;
	}

	return -1;
}

int WriteToFile(char* fileName, bookPosition bookHead) {
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "w");
	if (filePointer == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	bookPosition currentBook = bookHead->next;
	userPosition currentUser = NULL;
	while (currentBook != NULL) {
		fprintf(filePointer, "TITLE: %s\n", currentBook->title);
		fprintf(filePointer, "AUTHOR: %s\n", currentBook->author);
		fprintf(filePointer, "RELEASE YEAR: %d\n", currentBook->releaseYear);
		fprintf(filePointer, "AVAILABLE: %d\n", currentBook->available);
		fprintf(filePointer, "USERS: ");
		currentUser = bookHead->userHead;
		while (currentUser != NULL) {
			fprintf(filePointer, "%s\n", currentUser->name);
			currentUser = currentUser->next;
		}
		fprintf(filePointer, "\n");
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}

int ReadingUsers(char* fileName, bookPosition bookHead, char* title) {
	char userName[MAX_LENGTH] = { 0 };
	char userSurname[MAX_LENGTH] = { 0 };
	int numberOfBooks = 0;
	FILE* filePointerUsers = NULL;
	filePointerUsers = fopen(fileName, "r");
	if (filePointerUsers == NULL) {
		printf("Error opening %s file", fileName);
		return EXIT_FAILURE;
	}
	while (!feof(filePointerUsers)) {
		fscanf(filePointerUsers, "%s %s %d\n", userName, userSurname, &numberOfBooks);
		strcat(userName, " ");
		strcat(userName, userSurname);
		//AllUsersSorted(bookHead, userName, numberOfBooks);
		for (int i = 0; i < numberOfBooks; i++) {
			InsertUserToBook(bookHead, userName, title, 1);
		}
	}
	fclose(filePointerUsers);
	return EXIT_SUCCESS;
}

int CheckingUserNumberOfCertainBook(bookPosition bookHead, char* title, char* userName) {
	bookPosition currentBook = bookHead->next;
	userPosition currentUser = currentBook->userHead;
	while (currentBook != NULL) {
		if (strcmp(currentBook->title, title) == 0) {
			currentUser = currentBook->userHead;
			while (currentUser != NULL) {
				printf("%s = %s\n", currentUser->name, userName);
				if (strcmp(currentUser->name, userName) == 0) {
					return currentUser->booksNumber;
				}
				currentUser = currentUser->next;
			}
		}
		currentBook = currentBook->next;
	}
	return -1;
}

int BookReturn(bookPosition bookHead, char* userName, char* title, int returnNumber) {
	bookPosition currentBook = bookHead->next;
	userPosition currentUser = currentBook->userHead;
	userPosition previousUser = bookHead->userHead;
	while (currentBook != NULL) {
		if (strcmp(currentBook->title, title) == 0) {
			while (currentUser != NULL) {
				printf("%s = %s\n", currentUser->name, userName);
				currentUser = currentBook->userHead;
				previousUser = bookHead->userHead;//nesto lose triba se minjat bookHead
				if (strcmp(currentUser->name, userName) == 0) {
					currentUser->booksNumber = currentUser->booksNumber - returnNumber;
					FreeMemory(currentUser, previousUser);
				}
				previousUser = currentUser;
				currentUser = currentUser->next;
			}
		}
		currentBook = currentBook->next;
	}

	return EXIT_SUCCESS;
}

int FreeMemory(userPosition currentUser, userPosition previousUser) {
	previousUser->next = currentUser->next;
	printf("oslobadanje");
	free(currentUser);
	return EXIT_SUCCESS;
}
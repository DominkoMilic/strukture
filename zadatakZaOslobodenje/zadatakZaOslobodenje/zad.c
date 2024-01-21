#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_LENGTH (1024)
#define ID_LENGTH (15)


struct User;
typedef struct User* userPosition;
typedef struct User {
	char name[MAX_LENGTH];
	int booksNumber;
	userPosition next;
} user;


struct Book;
typedef struct Book* bookPosition;
typedef struct Book {
	char title[MAX_LENGTH];
	char author[MAX_LENGTH];
	char ID[ID_LENGTH];
	int releaseYear;
	int available;
	bookPosition next;
	userPosition userHead;
} book;


bookPosition CreateNewBook(char* title, char* author, int releaseYear, int available, char* bookID);
void AllBooksSorted(bookPosition bookHead, char* title, char* author, int releaseYear, int available, char* bookID);
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
void ChangingUserNumberOfBooks(bookPosition bookHead, char* userName);
int UsersAndTheirBooksPrint(bookPosition bookHead);
int UserWriteToFile(char* fileName, bookPosition currentBook, bookPosition bookHead);
int AllUserWriteToFile(char* fileName, bookPosition bookHead);
int NumberOfLoanedBooks(bookPosition currentBook);
int AddingUsersWithZeroBooks(bookPosition bookHead, char* filename);

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
	AddingUsersWithZeroBooks(&bookHead, "ID1234.txt");
	AllUserWriteToFile("ID1234.txt", &bookHead);

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
		UsersAndTheirBooksPrint(bookHead);
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
			printf("Sorry, but you already have 5 books\n");
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
		else if (currentlyAvailable == 0) {
			printf("sorry, but we don't have any %s left\n", title);
			break;
		}
		else if (currentlyAvailable < loanNumber) {
			printf("Sorry, but we only have %d of that book remaining, do you want to loan %d books?(yes/no)\n", currentlyAvailable, currentlyAvailable);
			char answer[10] = { 0 };
			scanf(" %s", answer);
			if (strcmp(answer, "yes") == 0)
			{
				for (int i = 0; i < currentlyAvailable; i++)
					InsertUserToBook(bookHead, name, title, 1);
				break;
			}
			else
				break;
		}
		for (int i = 0; i < loanNumber; i++)
			InsertUserToBook(bookHead, name, title, 1);
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
		if (returnNumber > numberOfUserCertainBook || numberOfUserCertainBook == 0) {
			printf("Sorry, but user %s don't have enough books titled %s\n", name, title);
		}
		else {
			for (int i = 0; i < returnNumber; i++)
				BookReturn(bookHead, name, title, 1);
		}

		break;
	}
	case 'h': {
		printf("saving to file library.txt...\n");
		WriteToFile(fileName, bookHead);
		AllUserWriteToFile("ID1234.txt", bookHead);
		break;
	}
	case 'x': {
		printf("exiting...");
		return;
	}
	default: {
		printf("Invalid choice\n");
	}
	}
	Menu(bookHead, fileName);
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
	fscanf(filePointer, "ALL USERS: ID1234\n");
	while (fscanf(filePointer, "TITLE: %1023[^\n]\n", title) == 1) {
		fscanf(filePointer, "AUTHOR: %1023[^\n]\n", author);
		fscanf(filePointer, "RELEASE YEAR: %d\n", &releaseYear);
		fscanf(filePointer, "AVAILABLE: %d\n", &available);
		fscanf(filePointer, "USERS: %1023[^\n]\n", bookID);
		strcpy(IDFile, bookID);
		strcat(IDFile, ".txt");
		AllBooksSorted(bookHead, title, author, releaseYear, available, bookID);
		ReadingUsers(IDFile, bookHead, title);
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
		for (int i = 0; i < numberOfBooks; i++) {
			InsertUserToBook(bookHead, userName, title, 1);
		}
	}
	fclose(filePointerUsers);
	return EXIT_SUCCESS;
}

int ReadingAllUsers(char* fileName, bookPosition bookHead) {
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
		for (int i = 0; i < numberOfBooks; i++) {
			AllUsersSorted(bookHead, userName, numberOfBooks);
		}
	}
	fclose(filePointerUsers);
	return EXIT_SUCCESS;
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

bookPosition CreateNewBook(char* title, char* author, int releaseYear, int available, char* bookID) {
	bookPosition newElement = NULL;
	newElement = (bookPosition)malloc(sizeof(book));
	if (!newElement) {
		printf("couldn't allocate memory");
		return NULL;
	}

	strcpy(newElement->title, title);
	strcpy(newElement->author, author);
	strcpy(newElement->ID, bookID);
	newElement->releaseYear = releaseYear;
	newElement->available = available;
	newElement->userHead = NULL;
	newElement->next = NULL;

	return newElement;
}


int AllUsersSorted(bookPosition bookHead, char* name, int numberOfBooks) {
	userPosition newElement = CreateNewUser(name, numberOfBooks);

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

void AllBooksSorted(bookPosition bookHead, char* title, char* author, int releaseYear, int available, char* bookID) {
	bookPosition newElement = CreateNewBook(title, author, releaseYear, available, bookID);
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

	//PrintUsers(bookHead);
}


void SearchByYear(bookPosition bookHead, int searchYear) {
	bookPosition current = bookHead->next;
	int counter = 0;
	while (current != NULL) {
		if (current->releaseYear == searchYear) {
			counter++;
			printf("TITLE: %s\n", current->title);
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
			printf("AVAILABLE: %d\n\n", current->available);
		}
		current = current->next;
	}
	if (counter == 0)
		printf("Sorry, we don't have any book from that author\n");
}

void InsertUserToBook(bookPosition bookHead, char* userName, char* title, int numberOfBooks) {
	AllUsersSorted(bookHead, userName, numberOfBooks);
	userPosition newUser = CreateNewUser(userName, 1);
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

	return 0;
}

int CheckingAvailableNumberOfBook(bookPosition bookHead, char* title) {
	bookPosition current = bookHead->next;
	while (current != NULL) {
		if (strcmp(current->title, title) == 0) {
			return current->available;
		}
		current = current->next;
	}

	return 0;
}

int UserWriteToFile(char* fileName, bookPosition currentBook, bookPosition bookHead) {
	FILE* filePointer = NULL;
	int userNumberOfBook = 0;
	filePointer = fopen(fileName, "w");
	if (filePointer == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	if (currentBook->userHead == NULL) {
		return EXIT_SUCCESS;
	}
	else if (currentBook->userHead->next == NULL) {
		userNumberOfBook = CheckingUserNumberOfCertainBook(bookHead, currentBook->title, currentBook->userHead->name);
		fprintf(filePointer, "%s %d\n", currentBook->userHead->name, currentBook->userHead->booksNumber);
	}
	userPosition currentUser = currentBook->userHead->next;
	userPosition previousUser = currentBook->userHead;
	while (previousUser != NULL) {
		if (strcmp(currentUser->name, previousUser->name) == 0 && currentUser != previousUser) {
			if (currentUser->next != NULL)
				currentUser = currentUser->next;
			previousUser = previousUser->next;
		}
		else {
			userNumberOfBook = CheckingUserNumberOfCertainBook(bookHead, currentBook->title, previousUser->name);
			fprintf(filePointer, "%s %d\n", previousUser->name, userNumberOfBook);
			if (currentUser->next != NULL)
				currentUser = currentUser->next;
			previousUser = previousUser->next;
		}
	}
	fclose(filePointer);
	return EXIT_SUCCESS;
}

int AllUserWriteToFile(char* fileName, bookPosition bookHead) {
	FILE* filePointer = NULL;
	int userNumberOfBook = 0;
	filePointer = fopen(fileName, "w");
	if (filePointer == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	userPosition currentUser = bookHead->userHead;
	while (currentUser != NULL) {
		fprintf(filePointer, "%s %d\n", currentUser->name, currentUser->booksNumber);
		currentUser = currentUser->next;
	}
	fclose(filePointer);
	return EXIT_SUCCESS;
}

int WriteToFile(char* fileName, bookPosition bookHead) {
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "w");
	if (filePointer == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	bookPosition currentBook = bookHead->next;
	char completeID[ID_LENGTH] = { 0 };
	int insertAvailable = 0;
	fprintf(filePointer, "ALL USERS: ID1234\n\n");
	while (currentBook != NULL) {
		fprintf(filePointer, "TITLE: %s\n", currentBook->title);
		fprintf(filePointer, "AUTHOR: %s\n", currentBook->author);
		fprintf(filePointer, "RELEASE YEAR: %d\n", currentBook->releaseYear);
		insertAvailable = currentBook->available + NumberOfLoanedBooks(currentBook);
		fprintf(filePointer, "AVAILABLE: %d\n", insertAvailable);
		fprintf(filePointer, "USERS: %s\n", currentBook->ID);
		strcpy(completeID, currentBook->ID);
		strcat(completeID, ".txt");
		UserWriteToFile(completeID, currentBook, bookHead);
		fprintf(filePointer, "\n");
		currentBook = currentBook->next;
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}


int CheckingUserNumberOfCertainBook(bookPosition bookHead, char* title, char* userName) {
	bookPosition currentBook = bookHead->next;
	userPosition currentUser = currentBook->userHead;
	int counter = 0;
	while (currentBook != NULL) {
		counter = 0;
		if (strcmp(currentBook->title, title) == 0) {
			currentUser = currentBook->userHead;
			while (currentUser != NULL) {
				if (strcmp(currentUser->name, userName) == 0) {
					counter++;
				}
				currentUser = currentUser->next;
			}
			return counter;
		}
		currentBook = currentBook->next;
	}
	return 0;
}

int BookReturn(bookPosition bookHead, char* userName, char* title, int returnNumber) {
	bookPosition currentBook = bookHead->next;
	userPosition currentUser = currentBook->userHead;
	userPosition previousUser = NULL;
	while (currentBook != NULL) {
		if (strcmp(currentBook->title, title) == 0) {
			currentUser = currentBook->userHead;
			while (currentUser != NULL) {
				if (strcmp(currentUser->name, userName) == 0) {
					if (previousUser == NULL) {
						currentBook->userHead = currentUser->next;
						ChangingUserNumberOfBooks(bookHead, userName);
						currentBook->available++;
						free(currentUser);
						return EXIT_SUCCESS;
					}
					else {
						ChangingUserNumberOfBooks(bookHead, userName);
						currentBook->available++;
						FreeMemory(currentUser, previousUser);
						return EXIT_SUCCESS;
					}
				}
				previousUser = currentUser;
				currentUser = previousUser->next;
			}
		}
		currentBook = currentBook->next;
	}

	return EXIT_SUCCESS;
}

int FreeMemory(userPosition currentUser, userPosition previousUser) {
	previousUser->next = currentUser->next;
	free(currentUser);
	return EXIT_SUCCESS;
}

void ChangingUserNumberOfBooks(bookPosition bookHead, char* userName) {
	userPosition currentUser = bookHead->userHead;
	while (currentUser != NULL) {
		if (strcmp(userName, currentUser->name) == 0)
			currentUser->booksNumber--;
		currentUser = currentUser->next;
	}
}

int UsersAndTheirBooksPrint(bookPosition bookHead) {
	userPosition currentUser = bookHead->userHead;
	bookPosition currentBook = bookHead->next;
	int flag = 0;
	while (currentUser != NULL) {
		currentBook = bookHead->next;
		printf("%s:\n", currentUser->name);
		while (currentBook != NULL) {
			flag = 0;
			flag = CheckingUserNumberOfCertainBook(bookHead, currentBook->title, currentUser->name);
			if (flag > 0) {
				for (int i = 0; i < flag; i++)
					printf("%s\n", currentBook->title);
			}
			currentBook = currentBook->next;
		}
		printf("\n");
		currentUser = currentUser->next;
	}

	return EXIT_SUCCESS;
}

int NumberOfLoanedBooks(bookPosition currentBook) {
	userPosition currentUser = currentBook->userHead;
	int counter = 0;
	while (currentUser != NULL) {
		counter++;
		currentUser = currentUser->next;
	}
	return counter;
}

int AddingUsersWithZeroBooks(bookPosition bookHead, char* fileName) {
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "r");
	if (!filePointer) {
		perror("couldn't open file");
		return EXIT_FAILURE;
	}
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int temp = 0;
	while (!feof(filePointer)) {
		fscanf(filePointer, "%s %s %d\n", name, surname, &temp);
		if (temp == 0) {
			strcat(name, " ");
			strcat(name, surname);
			AllUsersSorted(bookHead, name, 0);
		}
	}

	return EXIT_FAILURE;
}
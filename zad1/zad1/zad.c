#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define FILE_ERROR_OPEN -1

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_POINTS (15)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;


Student* allocateMemory(int noStudents);

Student* allocateMemory(int noStudents)
{
	Student* students = NULL;
	students = (Student*)malloc(noStudents*sizeof(Student));
	if (!students)
	{
		printf("neuspjesna alokacija memorije\n");
		return NULL;
	}
	return students;

}

Student* ReadStudents(int noStudents);

Student* ReadStudents(int noStudents)
{
	int counter = 0;
	FILE* filePointer = NULL;
	Student* students = NULL;
	students = allocateMemory(noStudents);

	filePointer = fopen("students.txt", "r");
	if (!filePointer)
	{
		printf("neuspjelo otvaranje datoteke\n");
		return NULL;
	}
	while (!feof(filePointer))
	{
		fscanf(filePointer, " %s %s %lf", students[counter].name, students[counter].surname, &students[counter].points);
		counter++;
	}
	
	fclose(filePointer);
	
	return students;
}


int readNoRowsInFile() {
	int cnt = 0, i = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	filePointer = fopen("students.txt", "r");
	if (!filePointer) {
		printf("greska u otvaranju");
		return FILE_ERROR_OPEN;
	}
	while (!feof(filePointer)) {
		if (fgetc(filePointer) == '\n')
			cnt++;
		i++;
	}

	return cnt;
}

double calculateRelativePoints(double points);

double calculateRelativePoints(double points)
{
	return ((points / MAX_POINTS) * 100);
}

int showStudents(int noStudents, Student* students);

int showStudents(int noStudents, Student* students)
{
	int counter = 0;

	for (counter; counter < noStudents; counter++)
	{
		printf("Name: %s Surname: %s Absolute points: %.2lf Relative points: %.2lf \n", students[counter].name,
			students[counter].surname, students[counter].points, calculateRelativePoints(students[counter].points));
	}

	return 0;
}

int main() {
	int noRows = 0;
	Student* students = NULL;
	noRows = readNoRowsInFile();
	printf("%d\n", noRows);
	if (noRows > 0)
	{
		students = ReadStudents(noRows);
		showStudents(noRows, students);
		free(students);
	}


	return 0;
}
#include <stdio.h>
#define MAX_SIZE 50
#define MAX_LINE 1024
#define FILE_ERROR_OPEN -1


typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;


int readNoRowsInFile(FILE* file) {
	int cnt = 0, i=0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	filePointer = fopen("students.txt", "r");
	if (!filePointer) {
		printf("greska u otvaranju");
		return FILE_ERROR_OPEN;
	}
	while(!feof(filePointer)){
            if(fgetc(filePointer)=='\n')
                cnt++;
            i++;
	}

	return cnt;
}


int main() {
    FILE* file;
	int noRows = 0;
    noRows=readNoRowsInFile(file);
    printf("%d", noRows);


	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define N 256

/* function name: Error
 * input: char* message
 * output: Print an error message and exit
 */
void Error(char* msg) {
	printf("Error: %s\n", msg);
	exit(1);
}

//void StartExam(char* name, char* student);
void main(int argc, char* args[]){
int fdExam, fdAnswer, wbytes, rbytes, i, j, count = 0, NumOfQuestion;
	char Num[N] = { 0 }, Q, A, out[N] = { 0 }, final[N] = { 0 }, FullName[N]={0}, name[N]={0}, student[N]={0};
	char* token = { 0 }, buffer[N]={0}, s[2] = { "\n" };
	strcpy(name, args[1]);
	strcpy(student, args[2]);
	strcpy(FullName, student);
	strcat(FullName, "_");
	strcat(FullName, name);
	if ((fdExam = open(name, O_RDONLY, 0777)) == -1) // Open Exam file
		Error("Problem with open Exam file");
	if ((rbytes = read(fdExam, buffer, N)) == -1) // Read number of questions from Exam file
		Error("Problem with read Number of questions");
	if ((fdAnswer = open(FullName, O_WRONLY | O_CREAT, 0777)) == -1)
		Error("Error opening File\n");
	for (i = 0; i < strlen(buffer); i++)
		printf("%c", buffer[i]);
	token = strtok(buffer, s);
	while ((token != NULL) && (count < 2)) {
		strcpy(Num, token);
		count++;
		token = strtok(NULL, s);
	}
	NumOfQuestion = atoi(Num);
	printf("\nInsert number of Question and Sol:\n");
	for (i = 0; i < NumOfQuestion; i++) {
		scanf("%c", &Q);    //out [0] = A
		getchar();
		scanf("%c", &A);
		getchar();
		out[(Q - '0') - 1] = A;
	}
	j = 0;
	for (i = 0; i < 2 * NumOfQuestion; i += 2) {

		final[i] = out[j];
		final[i + 1] = '\n';
		j++;
	}

	if ((wbytes = write(fdAnswer, final, strlen(final))) == -1) //writing the answers to the file
		Error("write error\n");

	close(fdAnswer);
	close(fdExam);
}

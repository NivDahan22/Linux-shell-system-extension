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

//void SolExam(char* name)
void main(int argc, char* args[]){
	int fdExam, fdAnswer, wbytes, rbytes, i, count = 0, NumOfQuestion;
	char Sol[N] = { "Sol_" }, Num[N] = { 0 }, answer[N]={0};
	char name[N]={0};
	char* token, buffer[N]={0}, s[2] = { "\n" };
	strcpy(name, args[1]);
	strcat(Sol, name); // Sol = Sol_test1
	if ((fdAnswer = open(Sol, O_WRONLY | O_CREAT, 0777)) == -1) // Create SolExam file as "Sol_test1"
		Error("Problem with create SolExam file");
	if ((fdExam = open(name, O_RDONLY, 0777)) == -1) // Open Exam file
		Error("Problem with open Exam file");
	if ((rbytes = read(fdExam, buffer, N)) == -1) // Read number of questions from Exam file
		Error("Problem with read Number of questions");
	token = strtok(buffer, s);
	while ((token != NULL) && (count < 2)) {
		strcpy(Num, token);
		count++;
		token = strtok(NULL, s);
	}
	NumOfQuestion = atoi(Num);
	for (i = 1; i <= NumOfQuestion; i++) {
		printf("Insert True Sol for Question %d:\n", i);
		fgets(answer, N, stdin);
		strcat(answer, s);
		if ((wbytes = write(fdAnswer, answer, strlen(answer))) == -1) // Write the 'question'
			Error("Problem with write answer");
		strcpy(answer, "");
		strcpy(buffer,"");
	}
	close(fdExam);
	close(fdAnswer);
}



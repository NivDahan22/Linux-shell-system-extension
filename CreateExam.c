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

//void main(char* stam, char* name, char* subject, char* teacher) 
void main(int argc, char* args[]){
	int fdExam, wbytes, i, j;
	char NumQuestion[N], s[3] = { "\n\n" }, s2[2] = { ":" }, s3[2] = { "\n" }, ch[N], Successfully[14] = { "Successfully\n" };
	char question[N]={0}, answer[N]={0};
	char name[N]={0}, subject[N]={0}, teacher[N]={0};
	printf("Insert number of question:\n");
	fgets(NumQuestion, N, stdin);
	strcpy(name, args[1]);
	strcpy(subject, args[2]);
	strcpy(teacher, args[3]);
	strcat(subject, s);
	if ((fdExam = open(name, O_WRONLY | O_CREAT, 0777)) == -1) // Create Exam file as "ExamFile"
		Error("Problem with create Exam file");
	if ((wbytes = write(fdExam, subject, strlen(subject))) == -1) // Write the 'subject' name in top of the file
		Error("Problem with write the subject");
	if (wbytes != strlen(subject)) // Check if we write the subject well
		Error("Bad subject write");
	strcat(NumQuestion, s);
	if ((wbytes = write(fdExam, NumQuestion, strlen(NumQuestion))) == -1) // Write the number of question
		Error("Problem with write the number of question");
	if (wbytes != strlen(NumQuestion)) // Check if we write the subject well
		Error("Bad NumQuestion write");
	for (i = 1; i <= atoi(NumQuestion); i++) {
		char MessageForQuestion[N] = { "Question " };
		printf("Insert question %d:\n", i);
		fgets(question, N, stdin);
		strcat(question, s3);
		ch[0] = ('0' + i);
		ch[1] = '\0';
		strcat(MessageForQuestion, ch);
		strcat(MessageForQuestion, s2);
		strcat(MessageForQuestion, s); // Question i: \n
		if ((wbytes = write(fdExam, MessageForQuestion,
				strlen(MessageForQuestion))) == -1) // Write the message of question
			Error("Problem with write the MessageForQuestion");
		if ((wbytes = write(fdExam, question, strlen(question))) == -1) // Write the  question
			Error("Problem with write the question");
		printf("Insert 4 answers:\n");
		for (j = 1; j <= 4; j++) {
			printf("%d.", j);
			fgets(answer, N, stdin);
			strcpy(ch, "   ");
			ch[3] = ('0' + j);
			ch[4] = '\0';
			strcat(ch, "."); //j.
			strcat(ch, answer); //j.answer
			strcat(ch, s3); //j.answer\n
			if ((wbytes = write(fdExam, ch, strlen(ch))) == -1) // Write the 'answer'
				Error("Problem with write answer number i");
			strcpy(ch, "");
			strcpy(question, "");
			strcpy(answer, "");
		}
	}
	if ((wbytes = write(fdExam, Successfully, strlen(Successfully))) == -1) // Write 'Successfully'
		Error("Problem with write Successfully at the end of the file");
	if ((wbytes = write(fdExam, teacher, strlen(teacher))) == -1) // Write 'teacher' name
		Error("Problem with write the name of teacher");
	close(fdExam);
}

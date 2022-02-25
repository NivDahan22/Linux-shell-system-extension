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

//void CheckExam(char* name, char* student);
void main(int argc, char* args[]){
	char buffer[N] = { 0 }, *token, s[2] = "\n",
			s1[2] = "_", out_name1[N] = ("Grade_"), in[N] = { "Sol_" },
			true[N][N] = { 0 }, ans[N][N] = { 0 }, final[N] = { 0 }, out[4] = { 0 };
	char str[N] = { 0 }, name[N]={0}, student[N]={0};
	int fd1, rbytes, wbytes, i, answers = 0,
			count = 0;

	strcpy(name, args[1]);
	strcpy(student, args[2]);
	strcpy(str, name);
	strcat(out_name1, student); //out=Grade_name
	strcat(out_name1, s1); //out=Grade_name_
	strcat(out_name1, str); //out= Grade_name_test.txt
	strcat(in, str); //in = Sol_test.txt

	strcpy(final, student);
	strcat(final, s1);
	strcat(final, str); //final = student_test.txt

	if ((fd1 = open(in, O_RDONLY, 0777)) == -1)
		Error("Error opening File\n");

	if ((rbytes = read(fd1, buffer, N)) == -1)
		Error("Cannot read the file!\n");

	token = strtok(buffer, s); //to divide the input until the \n
	while ((token != NULL) && (count < N)) {
		strcpy(true[count], token);
		count++;
		token = strtok(NULL, s);
	} ////true have the value of the right answers

	close(fd1);

	if ((fd1 = open(final, O_RDONLY, 0777)) == -1)
		Error("Error opening File\n");

	if ((rbytes = read(fd1, buffer, N)) == -1)
		Error("Cannot read the file!\n");
	count = 0;
	token = strtok(buffer, s); //to divide the input until the \n
	while ((token != NULL) && (count < N)) {
		strcpy(ans[count], token);
		count++;
		token = strtok(NULL, s);
	} ////true have the value of the right answers

	close(fd1);

	//count is the value of number of question

	for (i = 0; i < count; i++)
		if (strcmp(ans[i], true[i]) == 0)
			answers++;

	out[0] = ('0' + answers);
	out[1] = ('/');
	out[2] = ('0' + count);
	out[3] = ('\0');

	if ((fd1 = open(out_name1, O_WRONLY | O_CREAT, 0777)) == -1)
		Error("Error opening File\n");

	if ((wbytes = write(fd1, out, strlen(out))) == -1) //writing the answers to the file
		Error("write error\n");

	close(fd1);
}

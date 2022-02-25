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

//int CalcGrade(char* name, char* student);
int main(int argc, char* args[]){
	char buffer[N] = { 0 }, s2[2] = " ", s1[2] = "_", out_name1[N] = ("Grade_"), in[N] = {"\nFinal Grade:" }, final[3] = { 0 };
	int fd1, fd2, rbytes, wbytes, i, j, numofques = 0, sum = 0, answers = 0, count = 0;
	char str[N]={0}, name[N]={0}, student[N]={0};

	strcpy(name, args[1]); 
	strcpy(student, args[2]);
	strcpy(str, name);
	strcat(out_name1, student); //out=Grade_name
	strcat(out_name1, s1); //out=Grade_name_
	strcat(out_name1, str); //out= Grade_name_test

	if ((fd1 = open(out_name1, O_RDONLY, 0777)) == -1){
		printf("%s not found\n", name);
		return 0;
	}

	if ((rbytes = read(fd1, buffer, N)) == -1)
		Error("Cannot read the file!\n");

	close(fd1);

	sum = (buffer[0] - '0');
	answers = (buffer[2] - '0');

	strcat(buffer, in);

	count = (100 / answers) * sum;
	sum = count;
	if (count < 100) {

		final[1] = ((count % 10) + '0');
		final[0] = ((count / 10) + '0');
		final[2] = '\0';
		strcat(buffer, s2);
		strcat(buffer, final);
		strcat(buffer, "/100");

	} else {
		strcat(buffer, "100");
		strcat(buffer, "/100");
	}

	if ((fd1 = open(out_name1, O_WRONLY | O_CREAT, 0777)) == -1)
		Error("Error opening File\n");

	if ((wbytes = write(fd1, buffer, strlen(buffer))) == -1) { //writing the answers to the file
		Error("write error\n");
	}
	printf("%s\n", student);
	printf("%s", name);
	printf("\nYour final grade is %d\n", sum);
	close(fd1);
	return 0;
}

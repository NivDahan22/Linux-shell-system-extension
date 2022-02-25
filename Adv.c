#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define N 256

/* function name: CommandToSystem
 * input: char* command, int argc, 3 char* parameters
 * output: Sending an order(command) by execl and waiting for all the children
 */
void CommandToSystem(char* command, int argc, char* parameter1, char* parameter2, char* parameter3);

/* function name: Error
 * input: char* message
 * output: Print an error message and exit
 */
void Error(char* msg) {
	printf("Error: %s\n", msg);
	exit(1);
}

int main() {
	pid_t pid;
	int flag = 1, argc, i, temp=-1;
	char fullCommand[N]={0}, command[N]={0}, parameter1[N]={0}, parameter2[N]={0},
			parameter3[N]={0}, path[N]={"/home/braude/"}, path2[N]={"/bin/"};
	char* commandsArray[6] = {"CreateExam", "SolExam", "StartExam", "CheckExam", "CalcGrade", "GoodBye" };

	while (flag) {
		printf("AdvShell>"); // print AdvShell> every time
		fgets(fullCommand, N, stdin); // gets the full command from stdin
		argc = sscanf(fullCommand, "%s %s %s %s", command, parameter1, parameter2, parameter3); // Dividing the full command into four variables
		if (argc > 4) // Check if we get more parameters then we need
			Error("To much parameters\n");
		for (i = 0; i < 6; i++) { // For loop to check if the command is a system command or one of the new commands we added to commandsArray
			if ((strcmp(commandsArray[i], command)) == 0) { // if the command is one of the new commands that in commandsArray, go in
				temp = i;
				strcat(path,command); // path = /home/braude/command
			}
		}
		if(temp != i) // if the command is a system command
			strcat(path2, command); // path2 = /bin/command
		switch (temp) {
		case 0: //CreateExam function
			if((pid=fork()) == -1){
				perror("fork() failed\n");
				exit(1);
			}
			if(pid==0){
				execl(path,command, parameter1, parameter2, parameter3);
				perror("failed to do commandSystem(CreateExam)\n");
				exit(1);
			}
			break;
		case 1: //SolExam function
			if((pid=fork()) == -1){
				perror("fork() failed");
				exit(1);
			}
			if(pid==0){
				execl(path,command, parameter1);
				perror("failed to do commandSystem(SolExam)\n");
				exit(1);
			}
			break;
		case 2: //StartExam function
			if((pid=fork()) == -1){
				perror("fork() failed");
				exit(1);
			}
			if(pid==0){
				execl(path,command, parameter1, parameter2);
				perror("failed to do commandSystem(StartExam)\n");
				exit(1);
			}
			break;
		case 3: //CheckExam function
			if((pid=fork()) == -1){
				perror("fork() failed");
				exit(1);
			}
			if(pid==0){
				execl(path,command, parameter1, parameter2);
				perror("failed to do commandSystem(CheckExam)\n");
				exit(1);
			}
			break;
		case 4: //CalcGrade function
			if((pid=fork()) == -1){
				perror("fork() failed");
				exit(1);
			}
			if(pid==0){
				execl(path,command, parameter1, parameter2);
				perror("failed to do commandSystem(CalcGrade)\n");
				exit(1);
			}
			break;
		case 5: //GoodBye
			flag = 0; // flag get the value of 0 to go our from the while loop
			break;
		default: //CommandToSystem
			CommandToSystem(command, argc, parameter1, parameter2, parameter3); // Call function
			break;
		}
	wait(); // waiting for all the children
	strcpy(path,"/home/braude/");
	strcat(path2,"/bin/");
	strcat(fullCommand,"");
	strcat(command,"");
	strcat(parameter1,"");
	strcat(parameter2,"");
	strcat(parameter3,"");
	}
	return 0;
}

void CommandToSystem(char* command, int argc, char* parameter1, char* parameter2, char* parameter3) {
	pid_t pid;
	char path[N]={"/bin/"};
	strcat(path,command); // path = /bin/command
	if ((pid = fork()) == -1) {
		perror("fork() failed\n");
		exit(1);
	}
	if (pid == 0) {
		switch (argc) { // switch case on argc, to know hoe much parameters do i have
		case 1:
			execl(path, command, NULL);
			perror("Not Supported");
			exit(1);
		case 2:
			execl(path, command, parameter1, NULL);
			perror("Not Supported");
			exit(1);
		case 3:
			execl(path, command, parameter1, parameter2, NULL);
			perror("Not Supported");
			exit(1);
		case 4:
			execl(path, command, parameter1, parameter2, parameter3, NULL);
			perror("Not Supported");
			exit(1);
		}
		wait();
	}
}

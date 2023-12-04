#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit."
#define WAITING_FOR_INPUT_MESSAGE "\nenseash % "
#define BYEBYE_MESSAGE "Bye Bye...\n"
#define DEFAULT_MESSAGE "\nnot a function"
#define MAX_INPUT_SIZE 100

#include "question6.h"

int splitStringBySpaces(char * inputString, char ** outputString){
	//function to turn a char * into a char ** split by spaces
	int i = 0;
	
	char * token = strtok(inputString, " ");
	
	while (token != NULL){
		outputString[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	//execvp man pages : "the array must be terminated by a NULL pointer" :
	outputString[i] = NULL;
	
	return 0;
}

int main(int argc __attribute__((unused)), char **argv __attribute__((unused))){
	int status;
	char userInput[MAX_INPUT_SIZE];
	char * userInputSplitBySpaces[MAX_INPUT_SIZE];
	char signalexitCode[100];
	struct timespec start_time, end_time;

	//display welcome message
	write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));
	//display "enseash % "
	write(STDOUT_FILENO,WAITING_FOR_INPUT_MESSAGE,strlen(WAITING_FOR_INPUT_MESSAGE));
	
	while (1){
		//read user input
		read(STDOUT_FILENO,userInput,MAX_INPUT_SIZE);
		userInput[strcspn(userInput, "\n")] = '\0';
		
		splitStringBySpaces(userInput,userInputSplitBySpaces);
		
		if (!strcmp(userInput,"exit")){
			write(STDOUT_FILENO,BYEBYE_MESSAGE,strlen(BYEBYE_MESSAGE));
			return EXIT_SUCCESS;
		}
				
		//get start time
		clock_gettime(CLOCK_REALTIME,&start_time);
		
		//fork to keep the program running after a function call
		pid_t pid = fork();
		
		if (pid == 0){			
			//execute function inputed by user
			execvp(userInputSplitBySpaces[0],userInputSplitBySpaces);			
			return EXIT_FAILURE;
		}
		
		wait(&status);
		//get end time
		clock_gettime(CLOCK_REALTIME,&end_time);
		
		//display exit or signal code
		if (WIFEXITED(status)){
			snprintf(signalexitCode,MAX_INPUT_SIZE,"enseash [exit:%d|%ld ms] ",WEXITSTATUS(status),(end_time.tv_nsec - start_time.tv_nsec) / 1000000);
			write(STDOUT_FILENO,signalexitCode,strlen(signalexitCode));
		} else if(WIFSIGNALED(status)){
			snprintf(signalexitCode,MAX_INPUT_SIZE,"enseash [signal:%d|%ld ms] ",WTERMSIG(status),(end_time.tv_nsec - start_time.tv_nsec) / 1000000);
			write(STDOUT_FILENO,signalexitCode,strlen(signalexitCode));
		}
		write(STDOUT_FILENO,"% ",strlen("% "));
	}
}

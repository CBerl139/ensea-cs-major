#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit."
#define WAITING_FOR_INPUT_MESSAGE "\nenseash % "
#define BYEBYE_MESSAGE "Bye Bye...\n"
#define DEFAULT_MESSAGE "\nnot a function"
#define MAX_INPUT_SIZE 100

#include "question3.h"

int main(int argc, char *argv){
	char userInput[MAX_INPUT_SIZE];

	//display welcome message
	write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));
	
	while (1){
		//display "enseash % "
		write(STDOUT_FILENO,WAITING_FOR_INPUT_MESSAGE,strlen(WAITING_FOR_INPUT_MESSAGE));
		//read user input
		read(STDOUT_FILENO,userInput,MAX_INPUT_SIZE);
		userInput[strcspn(userInput, "\n")] = '\0';
		
		if (!strcmp(userInput,"exit")){
			write(STDOUT_FILENO,BYEBYE_MESSAGE,strlen(BYEBYE_MESSAGE));
			return EXIT_SUCCESS;
		}
		
		//fork to keep the program running after a function call
		pid_t pid = fork();
		
		if (pid == 0){
			//execute function inputed by user
			execlp(userInput,userInput,NULL);
			return EXIT_SUCCESS;
		}
		wait(NULL);
	}
}

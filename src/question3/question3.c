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
		write(STDOUT_FILENO,WAITING_FOR_INPUT_MESSAGE,strlen(WAITING_FOR_INPUT_MESSAGE));

		read(STDOUT_FILENO,userInput,MAX_INPUT_SIZE);
		//replace \n by \0 : (execlp man pages : "second argument must be terminated by a null pointer")
		userInput[strcspn(userInput, "\n")] = '\0';
		
		if (!strcmp(userInput,"exit")){
			write(STDOUT_FILENO,BYEBYE_MESSAGE,strlen(BYEBYE_MESSAGE));
			return EXIT_SUCCESS;
		}
		

		pid_t pid = fork();
		
		if (pid == 0){
			//execute function inputed by user
			execlp(userInput,userInput,NULL);
			//exit failure if input is not a function
			return EXIT_FAILURE;
		}
		wait(NULL);
	}
}

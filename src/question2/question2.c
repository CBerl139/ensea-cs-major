#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit."
#define TOO_MANY_ARGUMENTS "usage : ./enseash \n"
#define WAITING_FOR_INPUT_MESSAGE "\nenseash % "
#define BYEBYE_MESSAGE "\nBye Bye..."
#define DEFAULT_MESSAGE "\nnot a function"
#define MAX_INPUT_SIZE 100

#include "question2.h"

int main(int argc, char *argv){
	char userInput[MAX_INPUT_SIZE];
	
	if (argc != 1){
		write(STDOUT_FILENO,TOO_MANY_ARGUMENTS,strlen(TOO_MANY_ARGUMENTS));
	}
	
	write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));
	
	while (1){
		write(STDOUT_FILENO,WAITING_FOR_INPUT_MESSAGE,strlen(WAITING_FOR_INPUT_MESSAGE));
		read(STDOUT_FILENO,userInput,MAX_INPUT_SIZE);
		
		userInput[strcspn(userInput, "\n")] = '\0';
		
		//display enterred function (for debugging)
		//write(STDOUT_FILENO,userInput,strlen(userInput));
		
		execlp(userInput,userInput,NULL);
		
		/*
		if (userInput == "exit"){
			write(STDOUT_FILENO,BYEBYE_MESSAGE,strlen(BYEBYE_MESSAGE));
			return 0;
		} else {
			write(STDOUT_FILENO,DEFAULT_MESSAGE,strlen(DEFAULT_MESSAGE));	
		}
		*/
	}
}

char* fortune(void){
	return "test";
}

#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit."
#define WAITING_FOR_INPUT_MESSAGE "\nenseash % "
#define BYEBYE_MESSAGE "Bye Bye...\n"
#define DEFAULT_MESSAGE "\nnot a function"
#define MAX_INPUT_SIZE 100

#include "question4.h"

int main(int argc, char **argv){
	int status;
	char userInput[MAX_INPUT_SIZE];
	char signalexitCode[100];


	write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));
	write(STDOUT_FILENO,WAITING_FOR_INPUT_MESSAGE,strlen(WAITING_FOR_INPUT_MESSAGE));
	
	while (1){
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
			return EXIT_FAILURE;
		}
		
		wait(&status);
		
		//display exit or signal code
		if (WIFEXITED(status)){
			snprintf(signalexitCode,MAX_INPUT_SIZE,"enseash [exit:%d] ",WEXITSTATUS(status));
			write(STDOUT_FILENO,signalexitCode,strlen(signalexitCode));
		} else if(WIFSIGNALED(status)){
			snprintf(signalexitCode,MAX_INPUT_SIZE,"enseash [signal:%d] ",WTERMSIG(status));
			write(STDOUT_FILENO,signalexitCode,strlen(signalexitCode));
		}
		
		write(STDOUT_FILENO,"% ",strlen("% "));
	}
}

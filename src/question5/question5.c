#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit."
#define WAITING_FOR_INPUT_MESSAGE "\nenseash % "
#define BYEBYE_MESSAGE "Bye Bye...\n"
#define MAX_INPUT_SIZE 100

#include "question5.h"

int main(int argc __attribute__((unused)), char **argv __attribute__((unused))){
	int status;
	char userInput[MAX_INPUT_SIZE];
	char signalexitCode[100];
	struct timespec start_time, end_time;

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
				
		//get start time
		clock_gettime(CLOCK_REALTIME,&start_time);
		
		pid_t pid = fork();
		
		if (pid == 0){			
			//execute function inputed by user
			execlp(userInput,userInput,NULL);			
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

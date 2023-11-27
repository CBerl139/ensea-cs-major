#define MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash %\n"
#include "question1.h"

int main(void){
	write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE));
}

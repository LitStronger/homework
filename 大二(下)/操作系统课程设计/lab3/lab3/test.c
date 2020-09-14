#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(){
        pid_t pid = fork();
	char * argv[8] = {};	// storage arguments
	
        if(pid == 0){
		printf("child\n");
		
        	execvp("cmd1",argv);
                perror("fork");
                exit(1);
        }
	else{
		printf("father\n");
	}
        wait(NULL); 
}

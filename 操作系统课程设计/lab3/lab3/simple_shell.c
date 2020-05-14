#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void buf_parse(char *buf, char *argv[]);
void cmd_execute(char *buf, char *argv[]);

int main(){

	char buf[1024] = {};
        char * argv[8] = {};	// storage arguments

	while(1){
		printf("shell# ");
		memset(buf, 0x00, sizeof(buf));

		/* receive string */
		while(scanf("%[^\n]%*c", buf) == 0){  // return 0 means that user only input '\n', ignore it
			printf("shell# ");
			setbuf(stdin, NULL);	      // clear stdin(the '\n' mentioned above)
		}
		
		/* do parse */
		buf_parse(buf, argv);
		printf("buf:%s", buf);
		printf("argv[0]:%s argv[1]:%s argv[2]:%s\n", argv[0], argv[1], argv[2]);
		
		/* command execute */
		cmd_execute(buf, argv);
/*
		pid_t pid = fork();
		if(pid == 0){
			execvp(buf, argv);
			perror("fork");
			exit(1);
		}
		wait(NULL);
*/
	}
	return 0;
}

void buf_parse(char *buf, char *argv[]){

        int argc = 0;   // argument counter
        int status = 0; // new argument appear
        int i = 0;

        for(i = 0; buf[i] != '\0'; i++){
        	if(status==0 && !isspace(buf[i])){
	                argv[argc++] = buf + i;      //point to start bit of new argument in buf
                        status = 1;
                }
                else if(isspace(buf[i])){
                        status = 0;
                        buf[i] = '\0';               //replace ' ' with 0
                }
        }
	argv[argc] = NULL; 

}

void cmd_execute(char *buf, char *argv[]){
        pid_t pid = fork();
        if(pid == 0){
        	execvp(buf, argv);
                perror("fork");
                exit(1);
        }
        wait(NULL); 
}

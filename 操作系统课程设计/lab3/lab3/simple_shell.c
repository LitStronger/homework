#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void buf_parse(char *buf, char *argv[]);
void cmd_execute(char *buf, char *argv[]);
void redirect(char * argv[]);

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
		//printf("buf:%s", buf);
		//printf("argv[0]:%s argv[1]:%s argv[2]:%s\n", argv[0], argv[1], argv[2]);
		

		/* command execute */
		cmd_execute(buf, argv);

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
		printf("child\n");

		// find ">" then redierct
		redirect(argv);
		
        	execvp(buf, argv);
                perror("fork");
                exit(1);
        }
	else{
		printf("father\n");
	}
        wait(NULL); 
}

void redirect(char * argv[])
{
	int i;
	for(i=0; argv[i] != NULL; ++i)
	{
		if(strcmp(argv[i], ">") == 0) 
		{
			printf("find > \n");
	        	if(argv[i+1] == NULL){ // no argument after > 
		          	perror("command '>'[option]?");
				exit(1);
			}
	        	argv[i] = NULL; 
		        
			// parse，create/open file
	        	int fd =open(argv[i+1], O_RDWR|O_CREAT|O_TRUNC, 0664);
			printf("open file: %s\n", argv[i+1]);
		       	if(fd == -1){
				perror("open");
				exit( 1);
			}
		 
	      		// redirct
			printf("receive data1\n");
		       	dup2(fd, 1);
			printf("receive data2\n");
	        	close(fd);
			printf("receive data3\n");
		   }
	}
}

/*
		// find "|"
		for(i=0; argv[i] != NULL; ++i)
		{
			if(strcmp(argv[i], "|") == 0) 
		        {
				printf("find | \n");
		        	if(argv[i+1] == NULL){ // no argument after | 
		          		perror("command '|'[option]?");
			 		exit(1);
				}
		        	argv[i] = NULL; 
		        
				
				pid_t pid_latter =fork();// create new child process
				if(pid_latter == 0){
					printf("child_latter\n");
					int pfd[2];	 // pipe fd
					if(pipe(fd) < 0){
						printf("fail to create pipe\n");
						exit(0);
					}
					printf("redirect stdout/stdin to pipe\n");
			            	dup2(pfd[1], 1);// pipe input
			            	dup2(pfd[0], 0);// pipe output
				        close(pfd[0]);
				        close(pfd[1]);										
					//cmd execute
				
				} 
				
				
		        	if(fd == -1){
					perror("open");
					exit( 1);
				}	 

		       // redirct
			printf("receive data1\n");

			printf("receive data2\n");

			printf("receive data3\n");
		    }
		}		
		
*/	


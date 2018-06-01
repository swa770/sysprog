#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PROMPT "$>"
#define LINE_LENGTH 10

int main(void){
	char buffer[LINE_LENGTH];
	char c;
	int count, background;
	int status;
	pid_t pid;

	for(;;){
		// <Get the command>
		count=0;
		printf(PROMPT);
		while(1){
			// getchar receives all letters until EOF is sent
			c = getchar();
			 //Exit if first letter is EOF
			if(c == EOF) {
				exit(0);
			}
			// Too Long
			if (count > LINE_LENGTH){
				printf("Your Commnad exceeds maximum line length");
				count=0;
				printf(PROMPT);
				continue; // restart while-loop
			}
			// Get Word
			buffer[count] = c;
			count++;
			if (c =='\n'){
				if (count > 1){
					buffer[count-1] = 0;
					break; // exit while-loop
				}
				else {
					count=0;
					printf(PROMPT);
					continue;
				}
			}

		}
		printf("Execute this command... %s\n", buffer); 
		// check whether it's background task
		if (buffer[count-1] == '&') {
			if(count>0){
				background=1;
			} else {
				continue; // restart for-loop
			}
		}
		
		// create child process
		pid = fork();
		if (pid < 0){
			perror("failed to fork");
			exit(1);
		}
		if ( pid == 0){ // child
			exit(system(buffer));
		}
		
		if (background == 1){
			continue; // do not wait for the child
		}
		wait(&status); // wait for foreground task
		printf("%d\n", status);
	}
	
	
	
	return 0;
}

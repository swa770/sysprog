#include <stdlib.h>
#include <unistd.h>
int main(void){

	pid_t pid;
	
	pid = fork();
	if(pid == 0){ // child process
		exit(0);
	}
	for(;;){ // infinite loop never wait
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i=0;

int main(void){
    pid_t pid;

    pid = fork();
    if (pid==0){
        // child
	printf("my pid is %d\n", getpid());
	printf("my parent_pid is %d\n", getppid()); 
	while(i<100){
    	    i++;
	    printf("Child: i is %d\n", i);
	}
    } else {
    	// parent
	printf("my pid is %d\n", getpid());
	printf("my parent_pid is %d\n", getppid());
	while(i<100){
    	    i++;
	    printf("Parent: i is %d\n", i);
    	}
    }
    return 0;

}

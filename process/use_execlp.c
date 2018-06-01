#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    int i;
    for(i=0;i<argc;i++){
    	printf("%s\n", argv[i]);
    }

    if (argc < 2){
    	printf("No Extra Args\n");
	return 0;
    }
    execlp(argv[1],"new process", NULL);
    perror("failed to launch the new program");
    return 0;
}

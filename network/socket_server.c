/* Server Side Socket */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BACKLOG 5
#define PORT 5000
#define SERVER_IP "127.0.0.1"

void * receiving(void* sockfd){
    char msg [256];
    while(1){
        bzero((char *)msg, sizeof(msg));
        if(recv((int)sockfd, &msg, sizeof(msg),0) <= 0){
            perror("End to Receive the message");
            break;
        }
        printf("New Message: %s\n", msg);
        printf("> ");
    }
    pthread_exit(NULL);
}

void * sending(void* sockfd){
    char msg [256];
    bzero((char *)msg, sizeof(msg));
    strcpy(msg, "Welcome To MyChat !\n");
    if (send((int)sockfd, &msg, sizeof(msg), 0) < 0){
        perror("Failed to send the message");
        pthread_exit(NULL);
    }
    while(1){
        bzero((char *)msg, sizeof(msg));
        printf("> ");
        fgets(msg, sizeof(msg), stdin);
        if (msg[0] != '\n'){
            if (send((int)sockfd, &msg, sizeof(msg), 0) < 0){
                perror("Failed to send the message");
                break;
            }
        }
    }
    pthread_exit(NULL);
}

int startchat(int sockfd){
    int rc;
    pthread_t threads[2];

    rc = pthread_create(&threads[0], NULL, receiving, (void *) sockfd );
    if (rc < 0){
        perror("Failed to create a thread");
        return -1;
    }
    rc = pthread_create(&threads[1], NULL, sending, (void *) sockfd );
    if (rc <0) {
        perror("Failed to create a thread");
        return -1;
    }
    if (pthread_join(threads[0], NULL) < 0 ){
        perror("Failed to join the thread");
        return -1;
    }
    else {
        // After stop receiving the message
        // disallow a user to send the message
        if (pthread_cancel(threads[1]) < 0) {
            perror("Failed to cancel the thread for sending messages");
        } else {
            puts("Stop sending messages");
        }
    }
    return 0;
}

void sigint_handler(int signo){
    puts("Detect Ctrl-C. Your Session is now closing...");
    exit(1);
    // signal(SIGINT, SIG_DFL); //call default func
}

int main(int argc, char * argv[]){
    int sockfd;
    int newsockfd;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    // get socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("This is my socket fd number! %d\n", sockfd);

    // server address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // bind
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        close(sockfd);
        perror("Failed to bind the socket");
        exit(1);
    }
    printf("Successfully bind the socket to %s:%d\n",
        inet_ntoa(serv_addr.sin_addr),
        PORT
    );

    // listen
    listen(sockfd, BACKLOG);

    // accept
    bzero((char *) &cli_addr, sizeof(cli_addr));
    int clilen = sizeof(cli_addr);

    signal(SIGINT, sigint_handler);
    while(1){
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        printf("Connected with %s\n", inet_ntoa(cli_addr.sin_addr));

        if (fork()==0){ // child proess
            close(sockfd);
            puts("=== Start new session ===");
            startchat(newsockfd);
            puts("=== Session is closed ===");
            close(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }
    return 0;
}

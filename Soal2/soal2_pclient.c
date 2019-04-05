#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/shm.h>
#define PORT 6900

void *Proses(void*);
void *Output();
char buffer[1024] = {0};
int sock = 0, valread;

int main() {
    pthread_t proses, output;
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    pthread_create(&proses, NULL, Proses, NULL);
    pthread_create(&output, NULL, Output, NULL);
    pthread_join(proses, NULL);
    return 0;
}

void *Proses(void *argv){
    char car[100];
    while(1){
        scanf("%s", car);
        send(sock , car , strlen(car) , 0 );
    }
}

void *Output(){
    while(1){
        memset(buffer, '\0', sizeof(buffer));
        valread = recv(sock, buffer, 1024, 0);
        if(valread == 0)
            exit(EXIT_SUCCESS);
        printf("%s\n",buffer );
    }
}

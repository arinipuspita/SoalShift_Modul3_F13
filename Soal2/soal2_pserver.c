#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#define PORT 6900

int *stock;
int shmid;
void *Print(void*);
void *Proses(void*);

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);

int main() {
    pthread_t print, proses;
    key_t key = 6969;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0777);
    stock = shmat(shmid, NULL, 0);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    pthread_create(&proses, NULL, Proses, NULL);

    pthread_join(proses, NULL);
    return 0;
}

void *Proses(void *argv){
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    while(1){
        memset(buffer, '\0', sizeof(buffer));
        valread = recv(new_socket, buffer, 1024, 0);
        if(valread == 0)
            exit(EXIT_SUCCESS);
        if(strcmp(buffer, "beli") == 0){
            if(*stock == 0){
                char *car = "transaksi gagal";
                send(new_socket , car , strlen(car) , 0 );
            }
            else if(*stock > 0){
                char *car = "transaksi berhasil";
                send(new_socket , car , strlen(car) , 0 );
                *stock -= 1;
            }
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

void *Proses1(void*);
void *Proses2(void*);
int status;

int main(){
    pthread_t proses1, proses2;
    status = 0;
    pthread_create(&proses1, NULL, Proses1, NULL);
    pthread_create(&proses2, NULL, Proses2, NULL);
    pthread_join(proses1, NULL);
    pthread_join(proses2, NULL);
    printf("\n");
}

void *Proses1(void *argv){
    status += 1;
    while(status != 2){}
    system("ps -aux | head -n 11 > /home/nmhhabiby/Documents/FolderProses1/SimpanProses1.txt");
    status += 2;
    while(status != 6){}
    system("cd /home/nmhhabiby/Documents/FolderProses1/; zip KompresProses1.zip SimpanProses1.txt; rm SimpanProses1.txt");
    status += 7;
    while(status != 20){}
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    system("cd /home/nmhhabiby/Documents/FolderProses1/; unzip KompresProses1.zip");
}

void *Proses2(void *argv){
    status  += 1;
    while(status != 2){}
    system("ps -aux | head -n 11 > /home/nmhhabiby/Documents/FolderProses2/SimpanProses2.txt");
    status += 2;
    while(status != 6){}
    system("cd /home/nmhhabiby/Documents/FolderProses2/; zip KompresProses2.zip SimpanProses2.txt; rm SimpanProses2.txt");
    status += 7;
    while(status != 20){}
    sleep(15);
    system("cd /home/nmhhabiby/Documents/FolderProses2/; unzip KompresProses2.zip");
}

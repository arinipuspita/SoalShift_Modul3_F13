#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/shm.h>

void RestoreTerminal();
char getch();

void *Render();
void *Input();

int isExit;
int shmid;
int *stock;
char c;

int main(){
    key_t key = 6969;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0777);
    stock = shmat(shmid, NULL, 0);
    *stock = 0;
    system("clear");
    isExit = 0;
    pthread_t render, input;
    pthread_create(&render, NULL, Render, NULL);
    pthread_create(&input, NULL, Input, NULL);
    while(1){
        if(isExit == 1){
            shmdt(stock);
            shmctl(shmid, IPC_RMID, NULL);
            RestoreTerminal();
            exit(EXIT_SUCCESS);
        }
    }
}

void *Render(){
    while(1){
        printf("Shop\n");
        printf("Food stock : %d\n", *stock);
        printf("Choices\n1. Restock\n2. Exit\n");
        sleep(1);
        system("clear");
    }
}

void *Input(){
    while(1){
        c = getch();
        if(c == '1'){
            *stock += 1;
        }
        else if(c == '2'){
            isExit = 1;
        }
    }
}


struct termios old={0};
struct termios new={0};

char getch(){
    char buf=0;
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    new = old;
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
 }

 void RestoreTerminal(){
     tcsetattr(0, TCSANOW, &new);
     tcsetattr(0, TCSADRAIN, &new);
 }

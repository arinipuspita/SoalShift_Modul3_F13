#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

void *Akmal(void*);
void *Siraj(void*);
void *Proses(void*);

struct argv{
    int statAkmal;
    int statSiraj;
    int countAkmal;
    int countSiraj;
    int panggilAkmal;
    int panggilSiraj;
    int sleepAkmal;
    int sleepSiraj;
    int isExit;
};

int main(){
    pthread_t akmal, siraj, proses;
    struct argv *arg;
    arg = malloc(sizeof(struct argv));
    arg->statAkmal = 0;
    arg->statSiraj = 100;
    arg->countAkmal = 0;
    arg->countSiraj = 0;
    arg->panggilAkmal = 0;
    arg->panggilSiraj = 0;
    arg->isExit = 0;
    arg->sleepAkmal = 0;
    arg->sleepSiraj = 0;
    pthread_create(&proses, NULL, Proses, (void*)arg);
    pthread_create(&akmal, NULL, Akmal, (void*)arg);
    pthread_create(&siraj, NULL, Siraj, (void*)arg);
    while(1){
        if(arg->isExit == 1){
            exit(EXIT_SUCCESS);
        }
    }
    pthread_join(proses, NULL);
    pthread_join(akmal, NULL);
    pthread_join(siraj, NULL);
}

void *Akmal(void *argv){
    struct argv *data = (struct argv*)argv;
    while(1){
        if(data->panggilAkmal == 1){
            data->countAkmal += 1;
            data->statAkmal += 15;
            data->panggilAkmal = 0;
        }
        if(data->countAkmal == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            data->sleepSiraj = 10;
            data->countAkmal = 0;
        }
        if(data->statAkmal >= 100 && data->isExit == 0){
            printf("Agmal terbangun, mereka bangun pagi dan berolahraga\n");
            data->isExit = 1;
        }
        while(data->sleepAkmal > 0){
            data->sleepAkmal -= 1;
            sleep(1);
            data->panggilAkmal = 0;
        }
    }
}

void *Siraj(void *argv){
    struct argv *data = (struct argv*)argv;
    while(1){
        if(data->panggilSiraj == 1){
            data->countSiraj += 1;
            data->statSiraj -= 20;
            data->panggilSiraj = 0;
        }
        if(data->countSiraj == 3){
            printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
            data->sleepAkmal = 10;
            data->countSiraj = 0;
        }
        if(data->statSiraj <= 0 && data->isExit == 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            data->isExit = 1;
        }
        while(data->sleepSiraj > 0){
            data->sleepSiraj -= 1;
            sleep(1);
            data->panggilSiraj = 0;
        }
    }
}

void *Proses(void *argv){
    struct argv *data = (struct argv*)argv;
    char input[100];
    while(1){
        fgets(input, 100, stdin);
        if(strcmp(input, "Agmal Ayo Bangun\n") == 0){
            data->panggilAkmal = 1;
        }
        else if(strcmp(input, "Iraj Ayo Tidur\n") == 0){
            data->panggilSiraj = 1;
        }
        else if(strcmp(input, "All Status\n") == 0){
            printf("Agmal WakeUp_Status = %d\n", data->statAkmal);
            printf("Iraj Spirit_Status = %d\n", data->statSiraj);
        }
    }
}

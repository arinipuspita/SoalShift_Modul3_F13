#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/shm.h>
#define maxHunger 200
#define maxHigen 100
#define maxHp 300

void RestoreTerminal();
char getch();
char c;
int stateMenu;
int isExit;
int shmid;
int *stock;
int enemyHP;

void *Render();
void *Input();
void *StatusControl();
void *Hunger();
void *Hygiene();
void *Regen();
void *CheckStat();
void *Bath();

struct budak
{
    char name[10];
    int hunger;
    int hygiene;
    int health;
    int food;
    int bathCd;
};

struct budak *slave;

int main(){
    key_t key = 6969;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0777);
    stock = shmat(shmid, NULL, 0);
    c = 'z';
    stateMenu = 0;
    isExit = 0;
    system("clear");
    pthread_t hunger, regen, input, render, check, hygiene, bath;
    slave = malloc(sizeof(struct budak));
    //a
    printf("Masukkan nama budak mu (hanya boleh 1 kata, max 10 huruf) :\n");
    scanf("%s", slave->name);
    system("clear");

    slave->hunger = maxHunger;
    slave->hygiene = maxHigen;
    slave->health = maxHp;

    pthread_create(&hunger, NULL, Hunger, NULL);
    pthread_create(&regen, NULL, Regen, NULL);
    pthread_create(&input, NULL, Input, NULL);
    pthread_create(&render, NULL, Render, NULL);
    pthread_create(&check, NULL, CheckStat, NULL);
    pthread_create(&hygiene, NULL, Hygiene, NULL);
    pthread_create(&bath, NULL, Bath, NULL);

    while(1){
        if(isExit == 1){
            shmdt(stock);
            shmctl(shmid, IPC_RMID, NULL);
            RestoreTerminal();
            exit(EXIT_SUCCESS);
        }
    }
}

void *Input(){
    while(1){
        c = getch();
        if(stateMenu == 0){
            enemyHP = 100;
            if(c == '1'){
                if(slave->food > 0){
                    slave->food -= 1;
                    slave->hunger += 15;
                }
            }
            else if(c == '2'){
                if(slave->bathCd == 0){
                    slave->bathCd = 20;
                    slave->hygiene += 30;
                }
            }
            else if(c == '3'){
                stateMenu = 1;
            }
            else if(c == '4'){
                stateMenu = 2;
            }
            else if(c == '5')
                isExit = 1;
        }
        else if(stateMenu == 1){
            if(c == '1'){
                enemyHP -= 20;
                if(enemyHP <= 0){
                    printf("Player Menang\n");
                    stateMenu = 0;
                }
                slave->health -= 20;
            }
            else if(c == '2'){
                stateMenu = 0;
            }
        }
        else if(stateMenu == 2){
            if(c == '1'){
                if(*stock > 0){
                    *stock -= 1;
                    slave->food += 1;
                }
            }
            else if(c == '2'){
                stateMenu = 0;
            }
        }
    }
}

void *Render(){
    while(1){
        if(stateMenu == 0){
            printf("Standby Mode\n");
            printf("Health : %d\nHunger : %d\nHygiene : %d\n", slave->health, slave->hunger, slave->hygiene);
            printf("Food left : %d\nBath will be ready in %ds\n", slave->food, slave->bathCd);
            printf("Choices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
        }
        else if(stateMenu == 1){
            printf("Battle Mode\n");
            printf("Monster's Health : %d\nEnemy's Health : %d\n", slave->health, enemyHP);
            printf("Choice\n1. Attack\n2. Run\n");
        }
        else{
            printf("Shop Mode\n");
            printf("Shop food stock : %d\nYour food stock : %d\n", *stock, slave->food);
            printf("Choice\n1. Buy\n2. Back\n");
        }
        sleep(1);

        system("clear");
    }
}

void *Hunger(){
    while(1){
        sleep(10);
        if(stateMenu != 1)
            slave->hunger -= 5;
    }
}

void *Regen(){
    while(1){
        sleep(10);
        if(stateMenu != 1){
            slave->health += 5;
        }
    }
}

void *Bath(){
    while(1){
        while(slave->bathCd > 0){
            sleep(1);
            slave->bathCd -= 1;
        }
    }
}

void *Hygiene(){
    while(1){
        sleep(30);
        if(stateMenu != 1)
            slave->hygiene -= 10;
    }
}

void *CheckStat(){
    while(isExit != 1){
        if(slave->health <= 0){
            printf("AWWWWW, si %s mati karena kehabisan nyawa\n", slave->name);
            isExit = 1;
        }
        else if(slave->hunger <= 0){
            printf("AWWWWW, si %s mati karena kelaparan\n", slave->name);
            isExit = 1;
        }
        else if(slave->hygiene <= 0){
            printf("AWWWWW, si %s mati karena terlalu jorok\n", slave->name);
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

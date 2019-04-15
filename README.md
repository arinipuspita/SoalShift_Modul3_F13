# SoalShift_Modul3_F13
## Kelompok F13
## Arini Puspitasari (05111740000040)
## Nur Muhammad Husnul Habib Yahya (05111740000094)

## 1. Thread
### 1.1 Thread
Thread merupakan unit terkecil dalam suatu proses yang dapat dijadwalkan oleh sistem operasi. Thread biasanya terbentuk oleh fork yang berjalan pada suatu script atau program untuk sebuah proses. Minimal terdapat sebuah thread yang berjalan dalam suatu proses, walau biasanya terdapat lebih dari satu thread dalam proses tersebut. Thread akan berbagi memori dan menggunakan informasi (nilai) dari variabel-variabel pada suatu proses tersebut. Penggambaran thread pada sebuah proses dapat dilihat sebagai berikut.

thread

Untuk melihat thread yang sedang berjalan, gunakan perintah :

```top -H```
Thread dapat dibuat menggunakan fungsi pada program berbahasa C :
```
#include <pthread.h> //library thread

int pthread_create(pthread_t *restrict tidp,
                   const pthread_attr_t *restrict attr,
                   void *(*start_rtn)(void *),
                   void *restrict arg);
/* Jika berhasil mengembalikan nilai 0, jika error mengembalikan nilai 1 */
```
Penjelasan Syntax:

1. Pointer ```tidp``` digunakan untuk menunjukkan alamat memori dengan thread ID dari thread baru.
2. Argumen ```attr``` digunakan untuk menyesuaikan atribut yang digunakan oleh thread. nilai ```attr``` di-set ```NULL``` ketika thread menggunakan atribut default.
3. Thread yang baru dibuat akan berjalan dimulai dari fungsi ```start_rtn``` dalam fungsi thread.
4. Pointer ```arg``` digunakan untuk memberikan sebuah argumen ke fungsi ```start_rtn```, jika tidak diperlukan argumen, maka ```arg``` akan di-set ```NULL.```
Contoh membuat program tanpa menggunakan thread playtanpathread.c:
```
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t child;
	int i, stat;
	char *argv1[] = {"clear", NULL};
	char *argv2[] = {"xlogo", NULL};
	child = fork();
	if (child==0) {
		execv("/usr/bin/clear", argv1);
	}
	else
	{
		for(i=0;i<6;i++)
		{
			printf("%d\n",i);
			fflush(stdout);
			sleep(1);
		}
		execv("/usr/bin/xlogo", argv2);
	}
	
}
```
Contoh membuat program menggunakan thread playthread.c :

```compile dengan cara gcc -pthread -o [output] input.c```
```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[3]; //inisialisasi array untuk menampung thread dalam kasus ini ada 2 thread

int length=5; //inisialisasi jumlah untuk looping
void* playandcount(void *arg)
{
	char *argv1[] = {"clear", NULL};
	char *argv2[] = {"xlogo", NULL};
	unsigned long i=0;
	pthread_t id=pthread_self();
	int iter;
	if(pthread_equal(id,tid[0])) //thread untuk menjalankan counter
	{
		for(iter=0;iter<6;iter++)
		{
			printf("%d\n",iter);
			fflush(stdout);
			sleep(1);
		}
	}
	else if(pthread_equal(id,tid[1])) // thread menampilkan gambar
	{
		execv("/usr/bin/xlogo", argv2);
	}
	else if(pthread_equal(id,tid[2])) // thread menutup gambar
	{
		execv("/usr/bin/pkill", argv2);
	}

	return NULL;
}
int main(void)
{
	int i=0;
	int err;
	while(i<2) // loop sejumlah thread
	{
		err=pthread_create(&(tid[i]),NULL,&playandcount,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
		i++;
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	exit(0);
	return 0;
}
```
Kesimpulan : Terlihat ketika program menggunakan thread dapat menjalankan dua task secara bersamaan (task menampilkan gambar dan task timer).

### 1.2 Join Thread
Join thread adalah fungsi untuk melakukan penggabungan dengan thread lain yang telah berhenti (terminated). Bila thread yang ingin di-join belum dihentikan, maka fungsi ini akan menunggu hingga thread yang diinginkan berstatus ```Terminated```. Fungsi ```pthread_join()``` ini dapat dikatakan sebagai fungsi ```wait()``` pada proses, karena program (task) utama akan menunggu thread yang di-join-kan pada program utama tersebut. Kita tidak mengetahui program utama atau thread yang lebih dahulu menyelesaikan pekerjaannya.

Contoh program C Join_Thread thread_join.c:
```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //library thread

void *print_message_function( void *ptr );

int main()
{
    pthread_t thread1, thread2;//inisialisasi awal
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int  iret1, iret2;

    iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1); //membuat thread pertama
    if(iret1) //jika eror
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);//membuat thread kedua
    if(iret2)//jika gagal
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }

    printf("pthread_create() for thread 1 returns: %d\n",iret1);
    printf("pthread_create() for thread 2 returns: %d\n",iret2);

    // pthread_join( thread1, NULL);
    // pthread_join( thread2, NULL); 

    exit(EXIT_SUCCESS);
}

void *print_message_function( void *ptr )
{
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);

    for(int i=0;i<10;i++){
        printf("%s %d \n", message, i);
    }
}
```
Keterangan :

Pada program di atas, jika kita comment baris ```pthread_join```, maka hasil yang didapat tidak akan memunculkan tulisan Thread 1 dan Thread 2.
Jika pemanggilan fungsi ```pthread_join``` di-uncomment, maka program yang kita buat akan memunculkan tulisan Thread 1 dan Thread 2.
Kesimpulan : Pada program pertama tidak menjalankan fungsi ```print_message_function``` karena sebelum kedua thread dijadwalkan, program utama (kemungkinan) telah selesai dieksekusi sehingga tidak menjalankan fungsi bawaan pada thread. Pada percobaan kedua, fungsi ```pthread_join()``` digunakan untuk membuat program utama menunggu thread yang join hingga target thread selesai dieksekusi, dengan fungsi ini program utama di-suspend hingga target thread selesai dieksekusi.

Fungsi untuk terminasi thread
```
#include <pthread.h>
void pthread_exit(void *rval_ptr);
```
Argumen ```rval_ptr``` adalah pointer yang digunakan yang dapat diakses oleh fungsi ```pthread_join()``` agar dapat mengetahui status thread tersebut

Fungsi untuk melakukan join thread
```
int pthread_join(pthread_t thread, void **rval_ptr);
/* Jika berhasil mengembalikan nilai 0, jika error mengembalikan nilai 1 */
```
Fungsi akan menunda pekerjaan sampai status pointer rval_ptr dari fungsi pthread_exit() mengembalikan nilainya.

### 1.3 Mutual Exclusion
Disebut juga sebagai Mutex, yaitu suatu cara yang menjamin jika ada pekerjaan yang menggunakan variabel atau berkas digunakan juga oleh pekerjaan yang lain, maka pekerjaan lain tersebut akan mengeluarkan nilai dari pekerjaan sebelumnya.

Contoh program Simple Mutual_Exclusion threadmutex.c:
```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
 
pthread_t tid1, tid2;
int status;
int nomor;
 
void* tulis(void *arg)
{
    status = 0;
 
    printf("Masukan nomor : ");
    scanf("%d", &nomor);
 
    status = 1;
 
    return NULL;
}

void* baca(void *arg)
{
    while(status != 1)
    {

    }

    printf("Nomor %d\n", nomor);
}
 
int main(void)
{

    pthread_create(&(tid1), NULL, tulis, NULL);
    pthread_create(&(tid2), NULL, baca, NULL);
 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    return 0;
}
```
Keterangan :

1. Terdapat 2 buah thread yang berjalan dengan fungsi yang berbeda.
2. Sumber daya (variabel) yang digunakan kedua thread untuk mengeksekusi pekerjaannya sama.
3. Variabel ```status``` adalah contoh simple untuk mengendalikan jalannya thread.
Kesimpulan : Karena kita tidak mengetahui thread mana yang lebih dahulu mengeksekusi sebuah variable atau sumber daya pada program, kegunaan dari Mutex adalah untuk menjaga sumber daya suatu thread agar tidak digunakan oleh thread lain sebelum ia menyelesaikan pekerjaannya.

## 2. IPC (Interprocess Communication)
### 2.1 IPC
IPC (Interprocess Communication) adalah cara atau mekanisme pertukaran data antara satu proses dengan proses lain, baik pada komputer yang sama atau komputer jarak jauh yang terhubung melalui suatu jaringan.

### 2.2 Pipes
Pipe merupakan komunikasi sequensial antar proses yang saling terelasi. Kelemahannya, hanya dapat digunakan untuk proses yang saling berhubungan dan secara sequensial. Terdapat dua jenis pipe:

unnamed pipe : Komunikasi antara parent dan child proses.
named pipe : Biasa disebut sebagai FIFO, digunakan untuk komunikasi yang berjalan secara independen. Hanya bisa digunakan jika kedua proses menggunakan filesystem yang sama.
```$ ls | less```
Diagram :



Syntax in C languange :
```
int pipe(int fds[2]);

Parameters :
fd[0] will be the fd(file descriptor) for the 
read end of pipe.
fd[1] will be the fd for the write end of pipe.
Returns : 0 on Success.
-1 on error.
```
Example :
pipe1.c
```
// C program to illustrate 
// pipe system call in C 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

#define MSGSIZE 16 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 

int main() 
{ 
	char inbuf[MSGSIZE]; 
	int p[2], i; 

	if (pipe(p) < 0) 
		exit(1); 

	/* continued */
	/* write pipe */

	write(p[1], msg1, MSGSIZE); 
	write(p[1], msg2, MSGSIZE); 
	write(p[1], msg3, MSGSIZE); 

	for (i = 0; i < 3; i++) { 
		/* read pipe */
		read(p[0], inbuf, MSGSIZE); 
		printf("%s\n", inbuf); 
	} 
	return 0; 
} 
```
Output :
```
hello, world #1
hello, world #2
hello, world #3
```
Pipe dengan fork
Diagram :


Example :
pipe-fork
```
// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 
	// We use two pipes 
	// First pipe to send input string from parent 
	// Second pipe to send concatenated string from child 

	int fd1[2]; // Used to store two ends of first pipe 
	int fd2[2]; // Used to store two ends of second pipe 

	char fixed_str[] = "forgeeks.org"; 
	char input_str[100]; 
	pid_t p; 

	if (pipe(fd1)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 
	if (pipe(fd2)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 

	scanf("%s", input_str); 
	p = fork(); 

	if (p < 0) 
	{ 
		fprintf(stderr, "fork Failed" ); 
		return 1; 
	} 

	// Parent process 
	else if (p > 0) 
	{ 
		char concat_str[100]; 

		close(fd1[0]); // Close reading end of first pipe 

		// Write input string and close writing end of first 
		// pipe. 
		write(fd1[1], input_str, strlen(input_str)+1); 
		close(fd1[1]); 

		// Wait for child to send a string 
		wait(NULL); 

		close(fd2[1]); // Close writing end of second pipe 

		// Read string from child, print it and close 
		// reading end. 
		read(fd2[0], concat_str, 100); 
		printf("Concatenated string %s\n", concat_str); 
		close(fd2[0]); 
	} 

	// child process 
	else
	{ 
		close(fd1[1]); // Close writing end of first pipe 

		// Read a string using first pipe 
		char concat_str[100]; 
		read(fd1[0], concat_str, 100); 

		// Concatenate a fixed string with it 
		int k = strlen(concat_str); 
		int i; 
		for (i=0; i<strlen(fixed_str); i++) 
			concat_str[k++] = fixed_str[i]; 

		concat_str[k] = '\0'; // string ends with '\0' 

		// Close both reading ends 
		close(fd1[0]); 
		close(fd2[0]); 

		// Write concatenated string and close writing end 
		write(fd2[1], concat_str, strlen(concat_str)+1); 
		close(fd2[1]); 

		exit(0); 
	} 
} 
```
### 2.3 Sockets
Socket merupakan sebuah end-point dalam sebuah proses yang saling berkomunikasi. Biasanya socket digunakan untuk komunikasi antar proses pada komputer yang berbeda, namun dapat juga digunakan dalam komputer yang sama.

Diagram :


Example : socket-server.c socket-client.c

Server
```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
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

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}
```
Client
```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
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

    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
```
Jalankan proses server dulu, kemudian jalankan clientnya. Dan amati apa yang terjadi.

### 2.4 Message Queues
Merupakan komunikasi antar proses dimana proses tersebut menciptakan internal linked-list pada alamat kernel Sistem Operasi. Pesannya disebut sebagai queue sedangkan pengenalnya disebut queue ID. Queue ID berguna sebagai key untuk menandai pesan mana yang akan dikirim dan tujuan pengiriman pesannya.

### 2.5 Semaphores
Semaphore berbeda dengan jenis-jenis IPC yang lain. Pada pengaplikasiannya, semaphore merupakan sebuah counter yang digunakan untuk controlling resource oleh beberapa proses secara bersamaan.

Jika suatu counter block memory memiliki nilai positif, semaphore dapat menggunakan resource untuk prosesnya, dan mengurangi nilai counter block dengan 1 untuk menandai bahwa suatu block memory tengah digunakan.
Sebaliknya, jika semaphore bernilai 0, proses akan masuk pada mode sleep sampai semaphore bernilai lebih besar dari 0.
### 2.6 Shared Memory
Sebuah mekanisme mapping area(segments) dari suatu blok memory untuk digunakan bersama oleh beberapa proses. Sebuah proses akan menciptakan segment memory, kemudian proses lain yang diijinkan dapat mengakses memory tersebut. Shared memory merupakan cara yang efektif untuk melakukan pertukaran data antar program.

Example: Proses 1 Proses 2

Proses 1
```
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void main()
{
        key_t key = 1234;
        int *value;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        value = shmat(shmid, NULL, 0);

        *value = 10;

        printf("Program 1 : %d\n", *value);

        sleep(5);

        printf("Program 1: %d\n", *value);
        shmdt(value);
        shmctl(shmid, IPC_RMID, NULL);
}
```
Proses 2
```
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void main()
{
        key_t key = 1234;
        int *value;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        value = shmat(shmid, NULL, 0);

        printf("Program 1 : %d\n", *value);
	*value = 30;

        sleep(5);

        printf("Program 1: %d\n", *value);
        shmdt(value);
        shmctl(shmid, IPC_RMID, NULL);
}
```
Jalankan proses 1 terlebih dahulu, lalu proses 2. Hasilnya Proses 1
```
Program 1 : 10
Program 1 : 30
```
Proses 2
```
Program 1 : 10
Program 1 : 30
```
Appendix
Libraries documentation (and functions)
$ man {anything-you-want-to-know}
$ man mkfifo
$ man fcntl
### Soal Latihan
#### Latihan 1
Buatlah sebuah program multithreading yang dapat menyalin isi file baca.txt ke dalam file salin1.txt. Kemudian menyalin isi dari file salin1.txt ke dalam file salin2.txt!

Jawab :
```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

void *Salin1(void *argv);
void *Salin2(void *argv);

int main(){
    pthread_t salin1, salin2;
    
    pthread_create(&salin1, NULL, Salin1, NULL);
    pthread_create(&salin2, NULL, Salin2, NULL);
    
    pthread_join(salin1, NULL);
    pthread_join(salin2, NULL);
}

void *Salin1(void *argv){
    FILE *baca, *salin;
    baca = fopen("baca.txt", "r");
    salin = fopen("salin1.txt", "w");
    char c;
    while(fscanf(baca, "%c", &c) != EOF){
        fprintf(salin, "%c", c);
    }
    fclose(baca);
    fclose(salin);
}

void *Salin2(void *argv){
    FILE *baca, *salin;
    baca = fopen("salin1.txt", "r");
    salin = fopen("salin2.txt", "w");
    char c;
    while(fscanf(baca, "%c", &c) != EOF){
        fprintf(salin, "%c", c);
    }
    fclose(baca);
    fclose(salin);
}
```
#### Latihan 2
Buatlah sebuah program multithreading yang dapat menampilkan bilangan prima dari 1-N. program akan dieksekusi menggunakan thread sebanyak T dimana setiap thread akan melakukan pencarian bilangan prima dengan range N/T (range tiap thread berbeda), kemudian tiap thread akan menampilkan hasilnya.

misalkan N = 100 dan T=2; jadi thread 1 akan mencari bilangan prima dari 1-50 dan thread 2 akan mencari dari 51-100

Jawab :
```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

void *PrintPrima(void *ar);

struct argv
{
    int awal;
    int akhir;
};


int main(){
    int t;
    pthread_t threads[999];
    const int n;
    scanf("%d %d", &t, &n);
    int i;
    struct argv *ar;
    ar = malloc(n * sizeof(struct argv));
    int iret;
    for(i = 0; i < t; i++){
        if(i == 0){
            (ar + i)->awal = 2;
            (ar + i)->akhir = n /t;
        }
        else if(i == t - 1){
            (ar + i)->awal = (ar + i - 1)->akhir + 1;
            (ar + i)->akhir = n;
        }
        else{
            (ar + i)->awal = (ar + i - 1)->akhir + 1;
            (ar + i)->akhir = (n / t) * (i + 1);
        }
        if(pthread_create(&threads[i], NULL, PrintPrima, (void*) (ar + i)) != 0){
            fprintf(stderr, "error %d", i);
            break;
        }
    }
    for(i = 0; i < t; i++){
        pthread_join(threads[i], NULL);
    }
    exit(EXIT_SUCCESS);
}
int IsPrime(int x){
    int i;
    if(x <= 1){
        return 0;
    }
    else if(x == 2){
        return 1; 
    }
    for(i = 2; i < x/2; i++){
        if(x % i == 0)
            return 0;
    }
    return 1;
}

void *PrintPrima(void *ar){
    int awal, akhir;
    struct argv *arg = (struct argv*)ar;
    awal = arg->awal;
    akhir = arg->akhir;
    int i;
    for(i = awal; i <= akhir; i++){
        if(IsPrime(i) == 1)
            printf("%d\n", i);
    }
}
```
#### Latihan 3
Buatlah sebuah program untuk menampilkan file diurutan ketiga dari sebuah direktori. Dengan ketentuan :

menggunakan pipe.
menggunakan command ls, head, tail.

Jawab :
```
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{
    int fd1[2], fd2[2];
    int child1, child2;

    char *ls_argv[] = {"ls", NULL, NULL};
    char *head_argv[] = {"head", "-n3", NULL};
    char *tail_argv[] = {"tail", "-n1", NULL};

    if(pipe(fd1) == -1 || pipe(fd2) == -1){
        fprintf(stderr, "pipe fail");
        exit(EXIT_FAILURE);
    }

    child1 = fork();
    if(child1 < 0){
        fprintf(stderr, "fork 1 fail");
        exit(EXIT_FAILURE);
    }
    else if(child1 > 0){
        //parent
        wait(NULL);
        child2 = fork();
        if(child2 < 0){
            fprintf(stderr, "fork 2 fail");
            exit(EXIT_FAILURE);
        }
        else if(child2 > 0){
            //parent
            wait(NULL);
            printf("2");
            close(fd1[0]);
            close(fd1[1]);
            dup2(fd2[0], STDIN_FILENO);
            close(fd2[0]);
            close(fd2[1]);

            execvp("tail", tail_argv);
        }
        else{
            //child
            printf("1");
            dup2(fd1[0], STDIN_FILENO);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO);
            close(fd2[1]);

            execvp("head", head_argv);
        }
    }
    else{
        //child
        printf("0");
        close(fd1[0]);
        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);

        execvp("ls", ls_argv);
    }
} 
```
References
https://notes.shichao.io/apue/
https://www.gta.ufrj.br/ensino/eel878/sockets/index.html
http://advancedlinuxprogramming.com/alp-folder/alp-ch05-ipc.pdf
https://www.geeksforgeeks.org/socket-programming-cc/
https://www.geeksforgeeks.org/pipe-system-call/

### Soal 1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120

Jawaban :
1. Menghitung nilai faktorial yang diinginkan
```
void* faktorial(void* f)
{
    int* input;
    input = (int*) f; //harus dicasting karena address menyimpan alamat sedangkan alamat untuk semua tipe data panjangnya sama tapi ketika kita butuh value harus tau panjang memori yang digunakan
    int angka= *input;
    int i;
    long long simpan=1;
    for(i=1; i<=angka; i++) //menghitungnya dimulai dari 1, increament
    {
        simpan=simpan*i;
    }
    hasil[angka]=simpan;
    //return NULL;
}
```
2. Membuat thread agar bisa menjalankannya perintah secara parallel (banyak input)
3. Menggunakan join thread agar selesainya bersama (parallel)
4. Sorting nilai faktorial menggunakan bubblesorting dari terkecil ke terbesar
```
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 1; i <= n; i++)
       for (j = i + 1; j <= n; j++){  
           if (arr[i] > arr[j]){
                swap(&arr[j], &arr[i]);
           }
       }
} 
```
5. Munculkan nilai faktorial dengan berurutan
```
for(a=1; a<=panjang; a++)
    {
        printf("%d! = %lld\n", arr[a], hasil[arr[a]]);
    }
```

### Soal 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

	a. Terdapat 2 server: server penjual dan server pembeli
	b. 1 server hanya bisa terkoneksi dengan 1 client
	c. Server penjual dan server pembeli memiliki stok barang yang selalu sama
	d. Client yang terkoneksi ke server penjual hanya bisa menambah stok
		Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
	e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
		Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
	f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
		Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
		Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
	g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali
	h. Menggunakan thread, socket, shared memory

Jawaban :
1. Buat 2 client (soal2_client dan soal2_pclient) dan 2 server (soal2_server dan soal2_pserver)
2. Kedua server saling berhubungan serta berguna untuk menghitung stok barang yang ada
3. Setiap server berpasangan dengan 1 client (soal2_server dengan soal2_client dan soal2_pserver dengan soal2_pclient), keduanya dipasangkan menggunakan port yang sama
4. Apabila soal2_pclient bekerja dan berhasil melakukan transaksi maka jumlah stok barang di soal2_pserver berkurang begitu juga dengan soal2_server
5. Apabila soal2_client bekerja dan berhasil melakukan transaksi maka jumlah stok barang di soal2_server bertambah begitu juga dengan soal2_pserver
6. Setiap 5 detik sekali server penjual akan mencetak stoknya menggunakan
```
void *Print(void *argv){
    while(1){
        printf("%d\n", *stock);
        sleep(5);
    }
}
```

### Soal 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

	a. Terdapat 2 karakter Agmal dan Iraj
	b. Kedua karakter memiliki status yang unik
		Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
		Iraj memiliki Spirit_Status, di awal program memiliki status 100
		Terdapat 3 Fitur utama
			All Status, yaitu menampilkan status kedua sahabat
			   Ex: Agmal WakeUp_Status = 75 
			     Iraj Spirit_Status = 30
			“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
			“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
		Terdapat Kasus yang unik dimana:
			Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
			Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
		Program akan berhenti jika Salah Satu :
			WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
			Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
		Syarat Menggunakan Lebih dari 1 Thread

Jawaban :
1. Stat awal untuk Agmal 0 sedangkan stat awal untuk Iraj 100
2. Apabila fungsi Agmal dipanggil maka nilai Agmal bertambah 1
```
if(data->panggilAkmal == 1){
            data->countAkmal += 1;
            data->statAkmal += 15;
            data->panggilAkmal = 0;
        }
```
3. Apabila fungsi Iraj dipanggil maka nilai Iraj berkurang 20
```
if(data->panggilSiraj == 1){
            data->countSiraj += 1;
            data->statSiraj -= 20;
            data->panggilSiraj = 0;
        }
```
4. Apabila fungsi Agmal sudah dipanggil sebanyak 3 kali maka fungsi Iraj sleep selama 10 detik
```
if(data->countAkmal == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            data->sleepSiraj = 10;
            data->countAkmal = 0;
	    }
```
5. Apabila fungsi Iraj sudah dipanggil sebanyak 3 kali maka fungsi Agmal sleep selama 10 detik
```
if(data->countSiraj == 3){
            printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
            data->sleepAkmal = 10;
            data->countSiraj = 0;
        }
```
6. Apabila nilai Agmal sudah mencapai 100 ataupun nilai Iraj sudah 0 maka proses akan berhenti dan akan exit

### Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
	
	Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
	Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
	Ketika Mengekstrak file .zip juga harus secara bersama-sama
	Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
	Wajib Menggunakan Multithreading
	Boleh menggunakan system

Jawaban :
1. Buat 2 proses, proses1 berguna untuk file1 sedangkan proses2 untuk file2
2. Simpan list proses di SimpanProses1.txt
```
    status += 1;
    while(status != 2){}
    system("ps -aux | head -n 11 > /home/nmhhabiby/Documents/FolderProses1/SimpanProses1.txt");
```
3. Kompres file tersebut dengan format KompresProses1.zip dan hapus file SimpanProses1.txt
```
    status += 2;
    while(status != 6){}
    system("cd /home/nmhhabiby/Documents/FolderProses1/; zip KompresProses1.zip SimpanProses1.txt; rm SimpanProses1.txt");
```
4. Sleep program selama 15 detik dan zip kembali folder yang telah di kompres tadi
```
    status += 7;
    while(status != 20){}
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    system("cd /home/nmhhabiby/Documents/FolderProses1/; unzip KompresProses1.zip");
}
```
5. Simpan list proses di SimpanProses2.txt
```
    status += 1;
    while(status != 2){}
    system("ps -aux | head -n 11 > /home/nmhhabiby/Documents/FolderProses1/SimpanProses2.txt");
```
6. Kompres file tersebut dengan format KompresProses2.zip dan hapus file SimpanProses2.txt
```
    status += 2;
    while(status != 6){}
    system("cd /home/nmhhabiby/Documents/FolderProses2/; zip KompresProses2.zip SimpanProses2.txt; rm SimpanProses2.txt");
```
7. Sleep program selama 15 detik dan zip kembali folder yang telah di kompres tadi
```
    status += 7;
    while(status != 20){}
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    system("cd /home/nmhhabiby/Documents/FolderProses2/; unzip KompresProses2.zip");
}
```
8. Buat thread agar semua proses dilaksanakan secara bersama
```
int main(){
    pthread_t proses1, proses2;
    status = 0;
    pthread_create(&proses1, NULL, Proses1, NULL);
    pthread_create(&proses2, NULL, Proses2, NULL);
    pthread_join(proses1, NULL);
    pthread_join(proses2, NULL);
    printf("\n");
}
```

### Soal 5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
	
	a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
	b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
	c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
	d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
	e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
	f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
		Pembeli (terintegrasi dengan game)
			Dapat mengecek stok makanan yang ada di toko.
			Jika stok ada, pembeli dapat membeli makanan.
		Penjual (terpisah)
			Bisa mengecek stok makanan yang ada di toko
			Penjual dapat menambah stok makanan.
	Spesifikasi program:
	A. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
	B. Program terdiri dari 3 scene yaitu standby, battle, dan shop.
	C. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :
		Standby Mode
		Health : [health status]
		Hunger : [hunger status]
		Hygiene : [hygiene status]
		Food left : [your food stock]
		Bath will be ready in [cooldown]s
		Choices
		1. Eat
		2. Bath
		3. Battle
		4. Shop
		5. Exit
	D. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :
		Battle Mode
		Monster’s Health : [health status]
		Enemy’s Health : [enemy health status]
		Choices
		1. Attack
		2. Run
	E. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :
		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
		1. Buy
		2. Back
	F. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :
		Shop
		Food stock : [shop food stock]
		Choices
		1. Restock
		2. Exit
	G. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

Jawaban :
1. Buat shared memory
```
    key_t key = 6969;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0777);
    stock = shmat(shmid, NULL, 0);
    c = 'z';
    stateMenu = 0;
    isExit = 0;
    system("clear");
    pthread_t hunger, regen, input, render, check, hygiene, bath;
    slave = malloc(sizeof(struct budak));
```
2. Status awal untuk monster setelah dibuat
```
    slave->hunger = maxHunger;
    slave->hygiene = maxHigen;
    slave->health = maxHp;
```
3. Buat thread agar semua program dapat berjalan bersama
```
    pthread_create(&hunger, NULL, Hunger, NULL);
    pthread_create(&regen, NULL, Regen, NULL);
    pthread_create(&input, NULL, Input, NULL);
    pthread_create(&render, NULL, Render, NULL);
    pthread_create(&check, NULL, CheckStat, NULL);
    pthread_create(&hygiene, NULL, Hygiene, NULL);
    pthread_create(&bath, NULL, Bath, NULL);
 ```
 4. Terdapat fungsi input yang dijalankan secara terus menerus yang berfungsi untuk menampilkan menu dan memasukkan pilihan dari menu yang ditampilkan
 5. Fungsi Render digunakan untuk menampilkan daftar menu sesuai dengan state menu yang diminta pada fungsi inout
 6. Apabila stateMenu==0 maka akan menampilkan menu standby mode
 ```
 	    if(stateMenu == 0){
            printf("Standby Mode\n");
            printf("Health : %d\nHunger : %d\nHygiene : %d\n", slave->health, slave->hunger, slave->hygiene);
            printf("Food left : %d\nBath will be ready in %ds\n", slave->food, slave->bathCd);
            printf("Choices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
        }
```
7. Apabila stateMenu==1 maka akan menampilkan menu battle mode
 ```
 	    printf("Battle Mode\n");
            printf("Monster's Health : %d\nEnemy's Health : %d\n", slave->health, enemyHP);
            printf("Choice\n1. Attack\n2. Run\n");
        }
```
8. Apabila stateMenu bernilai selain 0 atau 1 maka akan menampilkan menu shop mode
 ```
 	    printf("Shop Mode\n");
            printf("Shop food stock : %d\nYour food stock : %d\n", *stock, slave->food);
            printf("Choice\n1. Buy\n2. Back\n");
	    }
```
9. Buat fungsi untuk Regen untuk mengupdate status health monster
```
void *Regen(){
    while(1){
        sleep(10);
        if(stateMenu != 1){
            slave->health += 5;
        }
    }
}
```
10. Buat fungsi untuk Regen untuk mengupdate status bath monster
```
void *Bath(){
    while(1){
        while(slave->bathCd > 0){
            sleep(1);
            slave->bathCd -= 1;
        }
    }
}
```
11. Buat fungsi untuk Regen untuk mengupdate status hygiene monster
```
void *Hygiene(){
    while(1){
        sleep(30);
        if(stateMenu != 1)
            slave->hygiene -= 10;
    }
}
```
12. Buat fungsi untuk checkstatus
```
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
```

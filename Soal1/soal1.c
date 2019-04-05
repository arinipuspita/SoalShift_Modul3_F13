#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

long long hasil[100];

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

void* faktorial(void* f)
{
    int* input;
    input = (int*) f; //harus dicasting karena address menyimpan alamat sedangkan alamat untuk semua tipe data panjangnya sama tapi ketika kita butuh value harus tau panjang memori yang digunakan
    int angka= *input;
    int i;
    long long simpan=1;
    for(i=1; i<=angka; i++)
    {
        simpan=simpan*i;
    }
    hasil[angka]=simpan;
    //return NULL;
}

int main (int count, char *string[])
{
    int panjang=count-1;
    int arr[panjang];
    int a;

    pthread_t tid[panjang];

    for(a=1; a<=panjang; a++)
    {
        arr[a]= atoi (string[a]);   
    }
    for(a=1; a<=panjang; a++)
    {
        pthread_create(&(tid[a]),NULL,&faktorial,&arr[a]);
    }
    for(a=1; a<=panjang; a++)
    {
        pthread_join(tid[a],NULL);
    }
    bubbleSort(arr, panjang);
    for(a=1; a<=panjang; a++)
    {
        printf("%d! = %lld\n", arr[a], hasil[arr[a]]);
    }
}

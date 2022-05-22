#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define QTD_PROD 2
#define QTD_CONS 4

int buf;

sem_t empty, full;

void *producer(void *p){
    long index = (long)p;
    int data;
    printf("[PROD-%ld] Iniciando...\n",index);
    while(1){
        data = rand() % 255;
        sem_wait(&empty);
        buf = data;
        printf("[PROD-%ld] Gerou valor %d\n", index, data);
        sem_post(&full);
    }

}
void *consumer(void *p){
    long index = (long)p;
    int result;
    printf("[CONS-%ld] Iniciando...\n",index);
    while(1){
        sem_wait(&full);
        result = buf;
        printf("[CONS-%ld] Consumiu o valor %d\n",index, result);
        sleep(1);
        sem_post(&empty);
    }
}


int main(void){

    time_t t;
    pthread_t produtores[QTD_PROD];
    pthread_t consumidores[QTD_CONS];

    sem_init(&empty, 0, 1); //empty = 1
    sem_init(&full, 0, 0); //full = 0

    srand((unsigned)time(&t));

    for(long i = 0; i < QTD_PROD; i++){
        pthread_create(&produtores[i], 0, producer,(void*)i);
    }
    for(long i = 0; i < QTD_CONS; i++){
        pthread_create(&consumidores[i], 0, consumer,(void*)i);
    }
    
    sleep(20);

    printf("Thread principal finalizando...");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
/*CODIGO DA ULTIMA AULA DO MEGA N PRODUTORES E N CONSUMIDORES
SE QUISER 1 CONSUMER PRA 5 PRODUCER OU VISSE E VERSA SO ALTERAR OS DEFINE*/
#define QTD_GENERATE 10
#define BUFFER_SIZE 8

#define QTD_PROD 2
#define QTD_CONS 5

int buf[BUFFER_SIZE];
int front = 0, rear = 0;
sem_t empty, full;
sem_t mutex_d, mutex_f;
int prod_active = 1;

void *prod(void *p){
    int valor_prod;
    int count = 0;

    long idx = (long)p;

    while(count < QTD_GENERATE){
        sem_wait(&empty);
        valor_prod = rand() % 255;
        printf("[PROD-%ld] %d\n", idx, valor_prod);
        sem_wait(&mutex_d);
        buf[rear] = valor_prod;
        sem_post(&mutex_d);
        rear = (rear+1) % BUFFER_SIZE;
        sleep(1);
        sem_post(&full);
        count++;
    }

}
void *cons(void *p){
    int valor_cons;
    int count = 0;
    long idx = (long)p;
    //while(count < QTD_GENERATE){
    while(prod_active){
        sem_wait(&full);
        sem_wait(&mutex_f);
        valor_cons = buf[front];
        sem_post(&mutex_f);
        front = (front + 1) % BUFFER_SIZE;
        printf("[CONS-%ld] %d\n", idx, valor_cons);
        sleep(2);
        sem_post(&empty);
        count++;
    }
}


int main(void){

    pthread_t _prod[QTD_PROD], _cons[QTD_CONS];
    time_t t;

    for(int i = 0; i < BUFFER_SIZE; i++)
            buf[i] = 0;
    

    srand(time(&t));

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex_d, 0, 1);
    sem_init(&mutex_f, 0, 1);

    for(long i = 0; i < QTD_PROD; i++){
        pthread_create(&_prod[i], NULL, prod, (void*)i);
    }
    for(long i = 0; i < QTD_CONS; i++){
        pthread_create(&_cons[i], NULL, cons, (void*)i);
    }
   

     for(long i = 0; i < QTD_CONS; i++){
        pthread_join(_cons[i], NULL);
    }

    prod_active = 0;
    sem_post(&mutex_f);
    sem_post(&full);

    for(long i = 0; i < QTD_PROD; i++){
         pthread_join(_prod[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex_d);
    sem_destroy(&mutex_f);


    return 0;
}
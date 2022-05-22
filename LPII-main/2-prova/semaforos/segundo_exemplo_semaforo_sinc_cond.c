#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define QTD_THREADS 5

sem_t arrive[QTD_THREADS];

void *worker(void *p){

    long index = (long)p;
    //worker task
    int sl = rand() % QTD_THREADS;
    sl++;
    printf("Worker %ld: tarefa de %d segundos\n", index,sl);
    sleep(sl);
    printf("Worker %ld chegou na barreira\n",index);
    sem_post(&arrive[index]);
    for(int i = 0; i < QTD_THREADS; i++){
        if(i != index){
            int sem_v;
            sem_getvalue(&arrive[i], &sem_v);
            if(sem_v !=0){
                sem_wait(&arrive[i]);
            }
        }
    }
    
    printf("Worker %ld passou da barreira\n", index);
}

int main(void){

    time_t t;
    pthread_t thread[QTD_THREADS];

    for(int i = 0; i < QTD_THREADS; i++){
        sem_init(&arrive[i], 0, 0);// inicializando os semaforos com 0
    }
    
   

    srand(time(&t));
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&thread[i], 0, worker, 0);
    }
    
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_join(thread[i], 0);
    }
    


    return 0;
}
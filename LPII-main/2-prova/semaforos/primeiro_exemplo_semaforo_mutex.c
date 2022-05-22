#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define QTD_THREADS 5

//solucao exclusao mutua utilizando semaforos

sem_t mutex;
int var_global = 0;
int repeat = 1;
void *cs(void *p){
    long index = (long)p;
    printf("[%ld] Iniciando...\n",index);
    while(repeat){
        sem_wait(&mutex);
        var_global++;
        printf("[%ld] ALterou var_global para %d\n",index, var_global);
        sleep(1);
        sem_post(&mutex);
        sleep(1);
    }
    printf("[%ld] Finalizando...\n",index);
}




int main(void){

    pthread_t threads[QTD_THREADS];

    sem_init(&mutex, 0 ,1);

    for(long i = 0; i <QTD_THREADS; i++){
        pthread_create(&threads[i], 0, cs, (void*)i);
    }
    sleep(20);

    repeat = 0;

    sleep(5);

    sem_close(&mutex);
    sem_destroy(&mutex);




    return 0;
}
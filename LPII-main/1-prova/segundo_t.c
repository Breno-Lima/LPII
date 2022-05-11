#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define QTD_THREADS 5
long var_global;

void *funcao_thread(void* param){
    long id = (long)param;
    printf("[%ld] Thread %ld criada!\n", id, id);
    sleep(5);
    var_global++;
    printf("[%ld] var_global = %ld\n", id, var_global);
    pthread_exit((void*) var_global + id);
}


int main(void){

    pthread_t threads[QTD_THREADS];
    var_global = 0;
    printf("[main] iniciando thread principal...\n");

    printf("[main] criando %d threads...\n", QTD_THREADS);

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i],NULL,funcao_thread,(void *)i)+1;
    }

    sleep(10);

    printf("[main] finalizando thread principal...\n");





    return 0;
}
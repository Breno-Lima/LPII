#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

/*
 process worker[i = 1 to n]{
        while (true){
            codigo da tarefa i;
            <count = count + 1;>
            <await (count == n);>
        }
    }
*/

#define QTD_THREADS 5

int contador_barreira = 0;

pthread_barrier_t controle_barreira;

void *worker(void *p){
    long idx = (long)p;

    while(1){

        printf("Thread %ld vai fazer sua tarefa\n", idx);
        puts("..");

        sleep(1 + idx); //simula uma tarefa

        printf("Thread %ld - terminou a tarefa, chegou na barreia\n", idx);
        puts("..");

        int wait_ret = pthread_barrier_wait(&controle_barreira);

        if((wait_ret != 0) && (wait_ret != PTHREAD_BARRIER_SERIAL_THREAD)){
            
            printf("BARRIER ERROR\n");
            exit(0);
        }
        /*
            __sync_fetch_and_add(&contador_barreira,1); //INCREMENTO ATOMICO
            printf("[%d] CONTADOR BARREIRA: %d\n, idx, contador barreira");
            puts("..");

            while(contador_barreira % QTD_THREADS != 0);

        */

       printf("Thread %ld - passou da barreira\n", idx);
       puts("..");

    }
}


int main(){

    pthread_t threads[QTD_THREADS];

    int init_bar_ret = pthread_barrier_init(&controle_barreira,NULL, QTD_THREADS);

    if(init_bar_ret != 0){
        printf("PTHREAD_BARRIER init error!\n");
        // if (init_bar_ret == EIVAL);
        // variavel de atributos passada para o init invalida
        // ou caontador de threads igual a zero
        // if(init_bar_ret == EIVAL)
        // ENOMEN - nao ha memoria disponivel
        //EAGIN - Nao ha recursos para criacao da barreira
        exit(0);
    }

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, worker, (void*)i);
    }

    sleep(30);

    printf("THread main vai finalizar...\n");
    puts("..");

    return 0;
}
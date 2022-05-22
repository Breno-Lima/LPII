#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

/*
bool lock = false;

process CS[i=1 to n]{
    while(true){
        <await (!lock) lock = true>//protocolo de entrada
        //secao critica
        lock = false; // protocolo de saida
        //secao nao critica
    }
}

*/

int lock = 0;
int varGLobal = 0;

pthread_mutex_t mutex_lock_control = PTHREAD_MUTEX_INITIALIZER;
//inicializacao da variavel de controle mutex

void *CS(void *p){
    long idx = (long)p;
    printf("[CS:%ld] Iniciando...\n",idx);
    while(1){
        /*
        while(_sync_lock_test_and_set(&lock, 1));
        //protocolo de entrada
        */

       pthread_mutex_lock(&mutex_lock_control); // protocolo de entrada
       //inicio da secao critica
       varGLobal++;
       printf("[CS:%ld] ALterou o valor para: %d\n",idx, varGLobal);
       puts("...");
       //usleep(90000);
       //sleep(1);// DESCOMENTE PARA GERAR STARVATION
       //SO THREAD 0 ACESSARA A SECAO CRITICA

       //fim da secao critica

       /*
        lock = 0; // protocolo de saida
       */

      pthread_mutex_unlock(&mutex_lock_control);//protocolo de saida
    }
}
int main(){

    pthread_t threads[5];

    for(long i = 0; i < 5; i++){
        pthread_create(&threads[0],NULL, CS, (void*)i);
    }

    sleep(20);








    return 0;
}
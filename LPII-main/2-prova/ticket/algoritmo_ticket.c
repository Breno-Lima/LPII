#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
//SOLUCAO JUSTA

/*

int number = 1, next = 1, turn[1:n] = ([n] 0)
n - numero de threads

process CS[i = 1 to n] {

    while(true){
        turn[i] = FA(number, 1); // protocolo de entrada
        while(turn[i] != next); // protocolo de entrada
        //secao critica
        <next = next + 1>        //protocolo de saida
        //secao nao critica
    }

}

*/


#define QTD_THREADS 5

int var_global = 0;
int number = 0;
int next = 0;
int turn[QTD_THREADS] = {0, 0, 0, 0, 0};

void *funcao_secao_critica(void* p){
    long id = (long)p;
    while(1){
        turn[id] = __sync_fetch_and_add(&number, 1);//protocolo de entrada
        while(turn[id] != next);                    //protocolo de entrada 
        var_global++; 
        printf("[%ld] var_global = %d\n",id, var_global);//secao critica
        sleep((rand()%5)+1);
        next++;                                     //protocolo de saida
    }                                    
}



int main(void){

    pthread_t threads[QTD_THREADS];

    printf("[main] ALgoritmo do ticket - %d threads\n", QTD_THREADS);
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, funcao_secao_critica, (void*)i);
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    } 

    return 0;
}
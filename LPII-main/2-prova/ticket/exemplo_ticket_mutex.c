#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
//codigo problematico
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

int varGLobal = 0;

int number = 1;
int next = 1;
int turn[QTD_THREADS];

pthread_mutex_t number_inc_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t condicao_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condicao_cond = PTHREAD_COND_INITIALIZER;

void *cs(void *p){
    long idx = (long)p;
    while(1){
        //turn[idx] = __sync_fetch_and_add(&number,1); -ATOMICO

        //EQUIVALENTE FUNCIONAL

        pthread_mutex_lock(&number_inc_mutex);
        number++;
        turn[idx] = number;
        pthread_mutex_unlock(&number_inc_mutex);

        //     while(!(turn[idx] == next));
        //pthread_mutex_lock(&condicao_mutex);
        if(turn[idx] % next == 0 ){
            pthread_cond_signal(&condicao_cond);
        }else{
            pthread_cond_wait(&condicao_cond,&condicao_mutex);
        }
      
        varGLobal++;
        printf("[CS-%ld] ALterou o valor para: %d\n", idx, varGLobal);
        puts("...");
        pthread_mutex_lock(&number_inc_mutex);
        next++;
        turn[idx] = number;
        pthread_mutex_unlock(&number_inc_mutex);
        // __sync_fecth_and_add(&next,1);
       pthread_mutex_unlock(&condicao_mutex);
        
        
    }
    return 0;
}
int main(){


    pthread_t threads[QTD_THREADS];

    for(int i = 0; i < QTD_THREADS; i++)
        turn[i] = 0;

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, cs, (void*)i);
    }
    
    sleep(10);



    return 0;
}
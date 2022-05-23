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
int carrinhocheio = 0;
int number = 1;
int next = 1;
int n1,n2 = 1;
int turn[QTD_THREADS];
int num_passenger;
pthread_mutex_t number_inc_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t condicao_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condicao_cond = PTHREAD_COND_INITIALIZER;

void *passageiro(void *p){
    long idx = (long)p;
    while(n2==1){
        while(carrinhocheio != 1){
            num_passenger = 0;
            n1 =1;
            pthread_mutex_lock(&number_inc_mutex);
            number++;
            pthread_mutex_unlock(&number_inc_mutex);

            if(varGLobal <= 4){
                pthread_cond_signal(&condicao_cond);
            }else{
                pthread_cond_wait(&condicao_cond,&condicao_mutex);
            }
            varGLobal++;
            idx++;
            
            printf("[Passageiro-%ld] Esperando para entrar no carrinho\n", idx);
            //sleep(1);
            
            printf("Passageiro %ld saiu\n",idx);
            //puts("...");
            pthread_mutex_lock(&number_inc_mutex);
            next++;
            turn[idx] = number;
            pthread_mutex_unlock(&number_inc_mutex);
            // __sync_fecth_and_add(&next,1);
            pthread_mutex_unlock(&condicao_mutex);
            n1 = 0;
            num_passenger++;
            
            sleep(1);
        }
        return 0;
    }
}

void *carro(void *p){
    long idx = (long)p;
    while(n1==1){
    n2 =1;
         //while(num_passenger == 3){
        if(idx == 3){
            printf("[carrinho-%d] Cheio!\n", varGLobal);
            printf("carrinho andando\n");
        }
            pthread_mutex_lock(&number_inc_mutex);
            number++;
            pthread_mutex_unlock(&number_inc_mutex);
            varGLobal++;
            //puts("...");
            pthread_mutex_lock(&number_inc_mutex);
            next++;
            turn[idx] = number;
            pthread_mutex_unlock(&number_inc_mutex);
            // __sync_fecth_and_add(&next,1);
            pthread_mutex_unlock(&condicao_mutex);
            n2 = 0;
            
            
            
            sleep(1);
        //}
        
        return 0;
    }
 
    
}


int main(){


    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,passageiro,NULL);  
    pthread_create(&thread2,NULL,carro,NULL);
    
    sleep(10);

    printf("Fim da funcao main!\n");

    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


/*
    -Primeira implementacao de trava (lock) a partir de pseudo
    codigo de andrews (contido nos slides)

    -Esta implementacao eh problematica pois seu protocolo de entrada
    nao eh executado de forma atomica, ou seja, podemos ter escalonamento durante
    o processo realizado por este protocolo, o que pode fazer com que de uma thread/processo
    acesse a secao critica
*/





int in1, in2;
int var_global;

void* cs1(void* p){
    while(1){
        //<await (!in2) in1 = 1;> //protocolo de entreda
        //protocolo de entrada
        while(in2 == 1);//so progride quando in2 for diferente de 1
        in1 = 1;
        //protocolo de entrada
        printf("cs1 na secao critica!\n");
        var_global++;
        sleep(3);
        printf("cs1: valor de var_global: %d\n",var_global);
        in1 = 0;//protocolo de saida
        printf("cs1 fora da secao critica!\n");
        sleep(1);
    }
}

void* cs2(void* p){
     while(1){
        //<await (!in1) in2 = 1;> //protocolo de entrada
        //protocolo de entrada
        while(in1 == 1);//so progride quando in2 for diferente de 1
        in2 = 1;
        //protocolo de entrada
        printf("cs2 na secao critica!\n");
        var_global++;
        sleep(3);
        printf("cs2: valor de var_global: %d\n",var_global);
        in2 = 0;//protocolo de saida
        printf("cs2 fora da secao critica!\n");
        sleep(1);
    }
}

int main(void){

    pthread_t thread1, thread2;
    in1 = 0;
    in2 = 0;
    
    var_global = 0;

    pthread_create(&thread1,NULL,cs1,NULL);  
    pthread_create(&thread2,NULL,cs2,NULL);

    sleep(20);

    return 0;
}
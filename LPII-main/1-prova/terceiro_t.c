#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#define QTD_THREADS 5

typedef struct{
    int index;
    char type;
    int data_chunk;

}pedaco_imagem;


void* processa_estrutura(void* param){
    pedaco_imagem meu_pedaco;
    meu_pedaco= (pedaco_imagem)param;
}


int main(void){
    time_t;
    struct pedaco_imagem imagem[QTD_THREADS];
    srand((unsigned) time(&t));


    for(int i = 0; i < QTD_THREADS; i++){
        imagem[i].index = i + 1;
        imagem[i].type = 65 + i;
        imagem[i].data_chunk = rand() % 255;
    }









    return 0;
}
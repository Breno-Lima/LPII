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

/*

    Para evitar a contencao de memoria que fatalmente vai acontecer quando tivermos
    muitas threads, entao veremos que a solucao nao vai ser mais ter um contador compartilhado
    mas sim ter um array que armazene cada uma das situacoes das threads se elas ja chegaram ou nao
    no ponto de embarreiramento, e uma vez que todas elas tenham chegado voce tem uma notificacao
    pra que elas sejam liberadas, entao voce nao tem todo mundo consultando a mesma variavel como 
    nesse exemplo.

*/

/*
    Para que nao haja a contecao de memoria podemos usar uma solucao que utiliza arrays
    para que as threads armazenem e notifiquem para as outras seus estados de tal forma que
    voce nao tenham contencao de memoria pq cada thread vai ter sua regiao de memoria especifica
    para manipular, entao isso elimina o problema da contencao de memoria, porem existe uma contrapartida
    quando voce coloca todas as informacoes pertinentes as outras threads nesse array, voce vai ter que
    ter uma thread a mais que sera a thread coordenadora que ficara olhando esse array para saber o que
    esta acontecendo, entao existe um tradeoff que eh justamente  a thread coordenadora
    


*/
#define QTD_THREADS 5

int entrada[QTD_THREADS];
int saida[QTD_THREADS];
int contador = 0;

void* processa_parte(void* p){
    long id = (long)p;
    /*codigo da tarefa*/
    while(1){
        printf("[%ld] iniciando tarefa...\n", id);
        saida[id] = pow(entrada[id], 2);
        printf("[%ld] Tarefa: %d\n", id, entrada[id]);
        printf("[%ld] Resultado tarefa: %d\n", id, saida[id]);
        sleep((int)(rand() % 3));
        printf("[%ld] Embairreirada, esperando as demais\n", id);
        /*fim codigo tarefa*/
        /*ponto de embarreiramento*/
        __sync_fetch_and_add(&contador, 1);
        while((contador != QTD_THREADS) != 0);

    }
}



int main(void){

    pthread_t threads[QTD_THREADS];

    time_t t;

    contador = 0;

    srand((unsigned) time(&t));
    
    for(int i = 0; i < QTD_THREADS; i++){
        entrada[i] = rand() % 100;
    }

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, processa_parte, (void*) i);
    }

    sleep(30);


    return 0;
}
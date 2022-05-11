#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
/*

    solucao sem contencao de memoria, contudo nao tem mt desempenho e consome muito da cpu
    pois os while consomem mt. Estamos fazendo espera ocupado o tempo inteiro, tanto no caso das
    travas como nessas barreiras.
    Espera ocupada eh uma solucao que so se usa quando temos recursos sobrando e precisamos de uma
    resposta imediata, para colocar um while pra quando assim que a condicao mudar,voce reagir, contudo
    esse requisito nao acontece sempre, voce pode ter uma latenciazinha entre a modificacao de uma codicao
    e a reacao a aquela modificacao.(por exemplo fazer uma alarme para uma hidreletrica que ta enchendo,
    voce nao pode esperar segundos ou milisegundos para reagir) O sistema que faria essa detectacao provavelmente
    estaria em um sistema embarcado/dedicado, entao poderia ficar nessa espera ocupada, so que essa
    situacao nao eh a situacao padrao.


*/
#define QTD_THREADS 5

int entrada[QTD_THREADS];
int saida[QTD_THREADS];

int arrive[QTD_THREADS];
int proceed[QTD_THREADS];

void* worker(void* p){

    long id = (long) p;
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
        arrive[id] = 1;
        while(proceed[id] != 1);
        //usleep(3000) se quiser diminuir o desempenha mas aliviar a cpu
        proceed[id] = 0;
        printf("[%ld] Saindo da barreira...\n", id);
    }
    return 0;
}

void *coordinator(void* p){
    while(1){
        for(int i = 0; i < QTD_THREADS; i++){
            while(arrive[i] == 0);
            //usleep(3000) se quiser diminuir o desempenha mas aliviar a cpu
            arrive[i] = 0;
        }
        printf("[coord] Barreira cheia, liberando...\n");
        for(int i = 0; i <  QTD_THREADS; i++){
            proceed[i] = 1;
        }
    }
    return 0;
}


int main(void){

    pthread_t threads[QTD_THREADS];
    pthread_t coord;
    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < QTD_THREADS; i++){
        entrada[i] = rand() % 100;
    }
    
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, worker, (void*)i);
    }

    pthread_create(&coord, NULL, coordinator, NULL);
    sleep(45);


    return 0;
}
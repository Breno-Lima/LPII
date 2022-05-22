/*1) Faça um programa em C/C++ em que você compare o tempo de criação de 30 
threads e 30 processos, onde as threads e processos criadas apenas executem
uma função que exiba uma mensagem ("Nova thread" ou "Novo processo") e as faça
dormir por 2s. Use alguma função de medição de tempo* para tal e escreva suas
impressões sobre o resultado, respondendo qual das opções demandou menos tempo
de execução para ser realizada e faça a relação disso com consumo de 
processamento e memória. Para finalizar, faça uma clara distinção (em 
comentários no código) das diferenças principais entre threads e processos.
 Ao término do programa, nenhum processo deverá permanecer em execução.

* Funções sugeridas para uso no processo de medição de tempo de execução são 
listadas abaixo. 
- Em C/C++: time(),  clock(), clock_gettime() (biblioteca time.h), 
  gettimeofday() (biblioteca sys/time.h);
- Em C++: método chrono::high_resolution_clock (biblioteca chrono). 
- Sugestão de referência: https://tinyurl.com/medirtempoemc
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#define QTD_THREADS 2
#define QTD_PROCESSOS 2
void* teste_thread(void* param){
    printf("Sou uma thread!\n");
    sleep(20);
    
    
}

int main(void){

    pthread_t thread[QTD_THREADS];
    clock_t inicio_t, inicio_f, fim_t, fim_f, result_t, result_f;
    int fork_return;

    inicio_t = clock();

    for(int i=0; i<QTD_THREADS; i++) {
        pthread_create(&(thread[i]), NULL, teste_thread, NULL);
    }
    fim_t = clock();

    inicio_f = clock();

    fork_return = fork();

       if(fork_return > 0){

           for(int i = 0; i < QTD_PROCESSOS - 2; i++){

               if(fork_return > 0)
                    fork_return = fork();
                    sleep(20);
                    
           }

       }
    printf("Sou um processo!");
    fim_f = clock();
    printf("O tempo de execucao dos processos foram: %lf\n",((double)(fim_f - inicio_f)/CLOCKS_PER_SEC));
    printf("O tempo de execucao das threads foram: %lf\n",((double)(fim_t - inicio_t)/CLOCKS_PER_SEC));


    return 0;
}
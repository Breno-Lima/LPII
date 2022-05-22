#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

    /*
        Quinto exemplo uso da funcao fork()
        -Invocacoes sucessivas a funcao fokr() para criacao de processos
        de acordo com a quantidade definida pelo usuario(clonarei quantidade-1,pois contamos com o processo original)
        - so o processo original se clona, controlando o nunmero de processos gerados
        
    */

int main(void){
    char c;
    int qtd_processos;
    int fork_return;
    int pid_original;

    pid_original = getpid();

    printf("Mensagem antes do fork() - pid original: %d\n", pid_original);

    printf("Digite a quantidade de processos a existir: ");

    /*
    
    Se a quantidade de processos for a que o usuario digitar
    voce contara o processo original (e o laço considera um indice a menos)
    
    */    

   scanf("%d", &qtd_processos);

   if(qtd_processos > 1){
       
       fork_return = fork();

       if(fork_return > 0){

           for(int i = 0; i < qtd_processos - 2; i++){
               //quantidade e processos -2 significa 
               //que contaremos com o processo original

               if(fork_return > 0)
                    fork_return = fork();
           }

       }

   }

    printf("Mensagem depois do fork()\n");
    sleep(15);
    printf("Processo finalizando... meu PID era: %d\n", getpid());
    return 0;
}
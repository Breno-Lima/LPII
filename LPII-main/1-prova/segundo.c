#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    int fork_return;
    char c;

    printf("Sou o processo original\n");
    printf("Mensagem antes da invocacao do fork()\n");
    printf("Meu PID: %d\n",getpid());
    printf("Aperte <ENTER> para clonar este processo: ");
    scanf("%c", &c);

    fork_return =fork();

    /*
        fork_return > 0 (execucao do processo pai)
        fork_return ==0 (execucao do processo clonado)
        fork_return == 1 (erro, nao houve clonagem)
        
    */


    if(fork_return > -1){
        
        if(fork_return == 0){
            // so sera executado pelo processo clonado
            printf("\nSou o processo clonado!\nretorno fork: %d", fork_return);
            sleep(20);
            printf("Sou o processo clonado e vou terminar... meu pid era: %d\n", getpid()); 

        }else{
            // so sera executado pelo processo original

            printf("\nSou o processo original!\nretorno do fork: %d\n", fork_return);
            sleep(20);
            printf("Sou o processo original e vou terminar... meu PID era: %d\n", getpid());

        }
    }else{

        printf("Erro ao invocar o fork()!\n");

    }
   
    return 0;
}
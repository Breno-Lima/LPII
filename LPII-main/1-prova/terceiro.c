#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


    /*
        Terceiro exemplo de uso da funcao fork()
        -Invocacoe sucessivas a funcao fork()
        -Processos dormem por 15s
        n = quantidade de forks
        2^n = quantidade de processos gerados
    */



int main(){

    char c;
    printf("Mensagem antes do fork()\n");
    printf("Aperte <ENTER> para clonar este processo:");
    scanf("%c",&c);

    fork(); //realizado so pelo original
    sleep(10); //existem 2 processo (original e clonado 1)

    fork(); //realizado pelo original e pelo primeiro clonado              
    sleep(10);//existem 4 processos (original, clonado 1, clonado 2, clonado3)
    
    fork();// realizado pelos 4 processos que ja existem
    //existem 8 processos (original, clonado 1...)

    printf("Mensagem depois do fork()\n");
    sleep(15);
    printf("Processo finalizado...\n");

    return 0;
    
}
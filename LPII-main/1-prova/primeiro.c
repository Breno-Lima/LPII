#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
    char c;
    printf("Programa que se clona\n");
    printf("Aperte qualquer tecla para clonar esta execucao:");
    scanf("%c",&c);
    fork();

    printf("Mensagem apos o fork (clongem)!/n");
    printf("Dormirei por 20s...\n\n");
    sleep(20);
    printf("Finalizando as duas instancias, pid desta: %d\n", getpid());
    

    return 0;
}
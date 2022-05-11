#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/*
    Processo original gera mais dois processos, e estes dormem um
    tempo aleatorio; o processo original aguarda o primeiro ser 
    finalizado e exibe informacoes capturadas atraves da funcao 
    wait()

*/

int main(void)
{
    char c;

    int fork_return;
    int fork_return2;

    printf("[O] Mensagem antes do fork()\n");
    printf("[O] Aperte <ENTER> para criar 2 processos: ");
    scanf("%c", &c);

    fork_return = fork();

    if (fork_return > 0)
    {
        //printf("Aperte <ENTER> para clonar este processo novamente: ");
        //scanf("%c", &c);
        //processo original
        fork_return2 = fork();
        if (fork_return2 > 0)
        {
            //processo original
            int exit_value, wait_value;

            wait_value = wait(&exit_value);

            printf("[O] Valor de saida do processo clonado: %d\n",
                   WEXITSTATUS(exit_value));

            printf("[O] PID do processo que finalizou primeiro: %d\n",
                   wait_value);
        }
        else
        {
            //segundo processo clonado
            printf("[2C] Sou o processo 2C, PID %d\n", getpid());
            srand(getpid());
            int dormir = rand() % 20;
            printf("[2C] Vou dormir %d s e sair...\n", dormir);
            sleep(dormir);
            exit(22);
        }
    }
    else
    {
        // primeiro processo clonado
        //segundo processo clonado
        printf("[1C] Sou o processo 1C, PID %d\n", getpid());
        srand(getpid());
        int dormir = rand() % 20;
        printf("[1C] Vou dormir %d s e sair...\n", dormir);
        sleep(dormir);
        exit(11);
    }

    printf("Processo original finalizando... meu PID era: %d\n", getpid());
    return 0;
}
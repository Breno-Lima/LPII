#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#define TAM_STR_HOST 100
#define TAM_MSG 100

int main(void){

    int meu_socket_stream;
    int connection_result;
    int porta_servidor;
    char host_servidor[TAM_STR_HOST];
    struct sockaddr_in endereco_srv;
    struct sockaddr_in endereco_recv;
    char msg[TAM_MSG];
    char msg_recv[TAM_MSG];

    printf("Digite o endereco do servidor: ");
    gets(host_servidor);

    printf("Digite a porta usada na conexao: ");
    scanf("%d", &porta_servidor);

    meu_socket_stream = socket(PF_INET, SOCK_STREAM, 0); //TCP

    bzero(&endereco_srv, sizeof(endereco_srv));

    endereco_srv.sin_family = AF_INET;
    endereco_srv.sin_port = htons(porta_servidor);
    inet_aton(host_servidor, &endereco_srv.sin_addr);

   connection_result = connect(meu_socket_stream, &endereco_srv, sizeof(endereco_srv));
    if(connection_result == 0){
        printf("Conectado ao servidor %s na porta %d\n", host_servidor, porta_servidor);
    }else{
        printf("Falha na conexao com servidor %s\n", host_servidor);
        exit(0);
    }

    while(1){
        printf("Digite uma mensagem: ");
        scanf(" %s", msg);
        //gets(msg);
        if(strcmp(msg, "exit")==0){
            close(meu_socket_stream);
            printf("Saindo...");
            exit(0);
        }
        sendto(meu_socket_stream, (void*)msg, strlen(msg), 0, &endereco_srv, sizeof(endereco_srv));
        recvfrom(meu_socket_stream, &msg_recv, TAM_MSG, 0, &endereco_recv, sizeof(&endereco_recv));
        printf("Mensagem do servidor: %s\n", msg_recv);
    }

    return 0;
}
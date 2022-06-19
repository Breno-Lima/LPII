#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TAM_STR_HOST 100
#define TAM_MSG 50

int main(void){
    
    int sock_fd;
    int client_fd;
    int client_info_len;
    unsigned int server_port = 0;
    struct sockaddr_in server_info;
    struct sockaddr_in client_info;

    printf("Digite a porta do servidor: ");
    scanf("%d", &server_port);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        printf("Problemas na criacao do socket!\n");
    }else{
        bzero(&server_info, sizeof(server_info));
        bzero(&client_info, sizeof(client_info));

        server_info.sin_family = AF_INET;
        server_info.sin_addr.s_addr = htonl(INADDR_ANY);
        server_info.sin_port = htons(server_port);

        if((bind(sock_fd, &server_info, sizeof(server_info))) != 0){
            printf("Problemas no bind()\n");
            exit(0);

        }else{

            printf("Aguardando conexoes na porta: %d\n", server_port);
           if(listen(sock_fd, 5) != 0){
                printf("\nErro ao invocar a funcao listen()\n");
                exit(0);
           }else{
                printf("...\n");
                client_fd = accept(sock_fd,(struct sockaddr *) &client_info, &client_info_len);
                if(client_fd < 0){
                    printf("\nErro ao invocar o accept!\n");
                    exit(0);
                }else{
                    printf("Cliente se conectou!\n");
                    char *client_ip_addr = inet_ntoa(client_info.sin_addr);
                    printf("Endereco: %s\n", client_ip_addr);
                    char *server_welcome_msg = "BEMVINDO";
                    write(client_fd, server_welcome_msg, strlen(server_welcome_msg));
                    while(1){
                        char buffer[TAM_MSG];
                        char msg_to_client[TAM_MSG];
                        int read_size;
                        read_size = recv(client_fd, buffer, TAM_MSG, 0);
                        if(read_size > 0){
                            printf("Client: %s\n", buffer);
                        }
                        
                        printf("Digite uma mensagem para enviar para o cliente: ");
                        scanf("%s",msg_to_client);

                        if(strcasecmp("exit", msg_to_client)==0){
                            close(client_fd);
                            exit(0);
                        }
                        write(client_fd, msg_to_client, strlen(msg_to_client));
                        }
                    }
                    
                }
           }
    }

    return 0;
}
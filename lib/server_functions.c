#include <stdio.h>
#include <stdlib.h> //exit
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio_ext.h>
#include "server_functions.h"
#include "log.h"
#include "server_handle_cli.h"

char log_message[400];

int srv_init(int port)
{
    int sockfd;
    SAI servaddr;
    

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        
        snprintf(log_message, sizeof(log_message),
        "Error en la creacion del socket. Codigo: %i\n", errno);

        log_error(log_message);

        exit(101);
    }

    const int enable = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
        
        snprintf(log_message, sizeof(log_message),
        "Error en la configuracion del socket. Codigo: %i\n", errno);

        log_error(log_message);

        exit(102);
    }

    //bzero para borrar los datos de un espacio de memoria.
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if( bind(sockfd, (SA*) &servaddr, sizeof(servaddr)) == -1){

        snprintf(log_message, sizeof(log_message),
        "Error en bind. Codigo: %i\n", errno);

        log_error(log_message);

        exit(112);
    }
    

    if( listen(sockfd, LISTENQ) == -1){

        snprintf(log_message, sizeof(log_message),
        "Error en listen. Codigo: %i\n", errno);

        log_error(log_message);

        exit(113);
    }

    printf("El socket esta escuchando en el puerto: %d\n", port);

    snprintf(log_message, sizeof(log_message),
    "El socket esta escuchando en el puerto: %d\n", port);
    
    log_event(log_message);

    return sockfd;
}

int srv_accept_client(int listenfd){
    SAI clientaddr;
    socklen_t clientaddrsize = sizeof(clientaddr);
    int connfd;
    
    while( (connfd = accept(listenfd, (SA*) &clientaddr, &clientaddrsize)) > 0){

        printf("Se ha aceptado una conexion desde %s", inet_ntoa(clientaddr.sin_addr));
        snprintf(log_message, sizeof(log_message), 
        "Se ha aceptado una conexion desde %s", inet_ntoa(clientaddr.sin_addr));
        log_event(log_message);
        
        
        
        return connfd;
    }

    return connfd;
}

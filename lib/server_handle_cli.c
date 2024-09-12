#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server_handle_cli.h"
#include "log.h"
#include "server_functions.h"

char message[4000];

void srv_handle_client(int socket){
    char buff[BUFF_LENGHT];
    int n;
    SAI addr;
    socklen_t addr_len = sizeof(addr);

    request req;

    bzero(buff, BUFF_LENGHT);

    if((n = recv(socket, buff, (BUFF_LENGHT-1), 0))> 0){
        buff[n] = '\0';
        //log_event(buff);
        parse_request(buff, &req);
        const char *http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nMensaje recibido correctamente";
        send(socket, http_response, strlen(http_response), 0);
        if(fputs(buff, stdout) == EOF){
            log_error("Error al leer el mensaje");
        }
    } else if (n<0){
        log_error("Error al recibir el mensaje");
    }

    if(strncmp(req.method, "GET", sizeof("GET")) != 0){
        log_error("EL METODO UTILIZADO NO ES GET");
    }

    getpeername(socket, (SA*)&addr, &addr_len);

    snprintf(message, sizeof(message),
            "El cliente %s:%d solicita [%s] con el metodo GET", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), req.url);
    log_event(message);
}

void parse_request(char *buff, request *req){
    char *method, *url;
    method = strtok(buff, " ");
    url = strtok(NULL, " ");
    strcpy(req->method, method);
    strcpy(req->url, url);
}
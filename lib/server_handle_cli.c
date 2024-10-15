#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server_handle_cli.h"
#include "log.h"
#include "server_functions.h"
#include "http_status_codes.h"
#include "file_handler.h"

char message[4000];

void srv_handle_client(int socket){
    char buff[BUFF_LENGHT];
    int n;
    SAI addr;
    socklen_t addr_len = sizeof(addr);

    request req;
    HttpResponse response;

    bzero(buff, BUFF_LENGHT);

    if((n = recv(socket, buff, (BUFF_LENGHT-1), 0))> 0){
        buff[n] = '\0';
        //log_event(buff);
        parse_request(buff, &req);
        //const char *http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nMensaje recibido correctamente";
        //send(socket, http_response, strlen(http_response), 0);
        if(fputs(buff, stdout) == EOF){
            log_error("Error al leer el mensaje");
        }
    } else if (n<0){
        log_error("Error al recibir el mensaje");
    }

    //Valida si el metodo es diferente a GET
    if(strncmp(req.method, "GET", sizeof("GET")) != 0){
        //log_error("EL METODO UTILIZADO NO ES GET");

        //Si no es get, devolvemos esta respuesta
        response.code = 404;
        response.content_type = "text/plain";
        response.datos = "Method Not Allowed";
    }else{

        response.datos = get_file_contents(req.url, &response.code);
        response.content_type = get_content_type(req.url);
    }

    //Validamos que la respuesta no venga vacia
    if( response.datos == NULL){
        response.code = 404;
        response.content_type = "text/plain";
        response.datos = "Datos nulos";
    }

    http_response(socket, response.code, response.content_type, response.datos);

    getpeername(socket, (SA*)&addr, &addr_len);

    snprintf(message, sizeof(message),
            "El cliente %s:%d solicita [%s] con el metodo GET", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), req.url);
    log_event(message);
}

void parse_request(char *buff, request *req){
    char *method, *url;
    method = strtok(buff, " ");
    url = strtok(NULL, " ");
    strncpy(req->method, method, sizeof(req->method)-1);
    strncpy(req->url, url, sizeof(req->url) -1);
}

void http_response(int socket, int code, const char *content_type, const char *data){
    char headers[512];

    sprintf(headers, "HTTP/1.1 %d %s\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",
    code, getMessage(code), content_type, strlen(data));

    
    if( data != NULL){
        send(socket, headers, strlen(headers), 0);
        send(socket, data, strlen(data), 0);
    }
    
}
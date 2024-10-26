#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server_handle_cli.h"
#include "log.h"
#include "server_functions.h"
#include "http_status_codes.h"
#include "file_handler.h"
#include <errno.h>

char message[4000];

void srv_handle_client(int socket){
    char buff[BUFF_LENGHT];
    int n, file_size;
    SAI addr;
    socklen_t addr_len = sizeof(addr);

    request req;
    HttpResponse response;

    bzero(buff, BUFF_LENGHT);

    if((n = recv(socket, buff, (BUFF_LENGHT-1), 0))> 0){
        buff[n] = '\0';

        if(fputs(buff, stdout) == EOF){
            log_error("Error al leer el mensaje");
        }

        parse_request(buff, &req);

    } else if (n<0){
        snprintf(message, sizeof(message), "Error al recibir el mensaje: %s", strerror(errno));
        log_error(message);
        close(socket);
        return;
    }

    //Valida si el metodo es diferente a GET
    if(strncmp(req.method, "GET", sizeof("GET")) != 0){
        //log_error("EL METODO UTILIZADO NO ES GET");

        //Si no es get, devolvemos esta respuesta
        response.code = 405;
        response.content_type = "text/plain";
        response.datos = "Method Not Allowed";
    }else{
        response.content_type = get_content_type(req.url);
        if (strstr(response.content_type, "image/") != NULL || strcmp(response.content_type, "application/octet-stream") == 0)
        {
            // Usar la función para archivos binarios
            unsigned char *data = get_binary_file_contents(req.url, &file_size, &response.code);
            if (data == NULL)
            {
                response.code = 404;
                response.content_type = "text/plain";
                response.datos = "Datos nulos";
            }
            else
            {
                // Enviar la respuesta HTTP
                http_binary_response(socket, response.code, response.content_type, (const char *)data, file_size);
                free(data); // Liberar memoria del buffer de datos binarios
            }
        }
        else
        {
            // Usar la función para archivos de texto
            response.datos = get_file_contents(req.url, &response.code);
            if (response.datos == NULL)
            {
                response.code = 404;
                response.content_type = "text/plain";
                response.datos = "Datos nulos";
            }
            else
            {
                http_response(socket, response.code, response.content_type, response.datos);
                free(response.datos); // Liberar memoria del buffer de datos de texto
            }
        }
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

    close(socket);
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

void http_binary_response(int socket, int code, const char *content_type, const char *data, size_t data_length)
{
    char headers[512];

    sprintf(headers, "HTTP/1.1 %d %s\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",
            code, getMessage(code), content_type, data_length);

    send(socket, headers, strlen(headers), 0);

    if (data != NULL && data_length > 0)
    {
        send(socket, data, data_length, 0); // Enviar la longitud correcta
    }
}
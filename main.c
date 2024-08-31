#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "lib/server_functions.h"
#include "lib/log.h"
#include <errno.h>

#define PORT 13
int main(){

    int escucharfd, conectarfd;

    escucharfd = srv_init(PORT);

    conectarfd = srv_accept_client(escucharfd);

    if(conectarfd == -1){
        log_error("Error al aceptar cliente.");
        fprintf(stderr, "Error en accept. Codigo: %i\n", errno);
        exit(114);
    }else{
        log_event("Conexion exitosa.");
    }

    close(conectarfd);
    close(escucharfd);
    return 0;
}
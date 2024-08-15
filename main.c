#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "lib/server_functions.h"
#include <errno.h>

#define PORT 13
int main(){

    int escucharfd, conectarfd;

    escucharfd = srv_init(PORT);

    conectarfd = srv_accept_client(escucharfd);

    if(conectarfd == -1){
        fprintf(stderr, "Error en accept. Codigo: %i\n", errno);
        exit(114);
    }

    close(conectarfd);
    close(escucharfd);
    return 0;
}
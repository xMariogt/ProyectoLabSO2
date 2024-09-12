#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "lib/server_functions.h"
#include "lib/log.h"
#include "lib/server_handle_cli.h"
#include <errno.h>

#define PORT 13

char msg[400];

int main(){

    int escucharfd, conectarfd;

    escucharfd = srv_init(PORT);

    
    while (1){
        conectarfd = srv_accept_client(escucharfd);
        srv_handle_client(conectarfd);

        if (conectarfd == -1)
        {   
            snprintf(msg, sizeof(msg),
            "Error en accept. Codigo: %i\n" ,errno);
            log_error(msg);
            break;
        }
        sleep(5);
        close(conectarfd);
    }
    
    close(escucharfd);
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "lib/server_functions.h"
#include "lib/log.h"
#include "lib/server_handle_cli.h"
#include "lib/queue.h"
#include <errno.h>

#define PORT 8080
#define THREAD_POOL_SIZE 10

char msg[400];

Queue connection_queue;
pthread_t thread_pool[THREAD_POOL_SIZE];

void *handle_multithread(void *arg)
{
    while (1)
    {
        int connfd = dequeue(&connection_queue);
        srv_handle_client(connfd);
        close(connfd);
    }
    return NULL;
}

int main(){

    int escucharfd, conectarfd;

    escucharfd = srv_init(PORT);

    init_queue(&connection_queue);

    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, handle_multithread, NULL);
    }

    while (1){
        conectarfd = srv_accept_client(escucharfd);
        srv_handle_client(conectarfd);

        if (conectarfd == -1)
        {   
            snprintf(msg, sizeof(msg),
            "Error en accept. Codigo: %i\n" ,errno);
            log_error(msg);
            continue;
        }
        enqueue(&connection_queue, conectarfd);
        //sleep(5);
        //close(conectarfd);
    }
    
    close(escucharfd);
    return 0;
}
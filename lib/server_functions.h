#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTION_H

#define SA struct sockaddr
#define SAI struct sockaddr_in
#define LISTENQ 15


int srv_init(int port);
int srv_accept_client(int listenfd);

#endif
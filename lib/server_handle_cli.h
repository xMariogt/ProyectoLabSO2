#ifndef SERVER_HANDLE_CLI_H
#define SERVER_HANDLE_CLI_H


#define BUFF_LENGHT 8192

typedef struct {
    char method[8];
    char url[2048];
} request;

void srv_handle_client();
void parse_request();


#endif
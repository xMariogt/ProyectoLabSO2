#ifndef SERVER_HANDLE_CLI_H
#define SERVER_HANDLE_CLI_H


#define BUFF_LENGHT 16192

typedef struct {
    char method[8];
    char url[2048];
} request;

typedef struct {
    int code;
    const char *content_type;
    char *datos;
} HttpResponse;

void srv_handle_client();
void parse_request();
void http_response(int client_socket, int http_code, const char *content_type, const char *data);
void http_binary_response(int socket, int code, const char *content_type, const char *data, size_t data_length);

#endif
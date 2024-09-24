#ifndef HTTP_STATUS_CODES_H
#define HTTP_STATUS_CODES_H

typedef struct {
    int code;
    char *message;
} HttpStatus;

char* getMessage(int code);


#endif
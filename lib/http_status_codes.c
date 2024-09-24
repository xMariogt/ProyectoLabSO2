#include <stdlib.h>
#include <string.h>
#include "http_status_codes.h"

const HttpStatus httpStatuses[] = {
    {200, "OK"},
    {400, "Bad Request"},
    {405, "Method Not Allowed"},
    {404, "Not Found"},
    {500, "Internal Server Error"}
};


char* getMessage(int code){
    for (int i =0; i < sizeof(httpStatuses); i++ ){
        if(httpStatuses[i].code == code){
            return httpStatuses[i].message;
        }
    }
    return "Codigo desconocido";
}


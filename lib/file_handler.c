#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file_handler.h"
#include "log.h"

#define BUFFERSIZE 1024

char *get_file_contents(char *url, int *httpCode){
    FILE *f;
    char *buffer = malloc(BUFFERSIZE);
    char *content = malloc(1);
    content[0] = '\0';
    size_t total_size= 0;
    char path[256]= PATH;

    //Valida que la url no venga vacia, si viene vacia entonces muestra el index
    if(strlen(url) == 0){
        strcat(path, "index.html");
    }else{
        strcat(path, url);
    }

    //Ahora se abre el archivo solicitado
    
    f = fopen(path, "r");

    if(!f){
        *httpCode = 404;
        log_error("Error al abrir el archivo1");
        strncpy(path, PATH, sizeof(PATH));
        strcat(path, "index.html");
        f = fopen(path, "r");

        

        if(!f){
            log_error("Error al abrir el archivo2");
            free(buffer);
            return NULL;
        }
    }
    
    while(fgets(buffer, BUFFERSIZE, f)){
        size_t buffer_len = strlen(buffer);
        content = realloc(content, total_size + buffer_len + 1);
        if(content == NULL){
            log_error("Buffer Vacio");
            free(buffer);
            fclose(f);
            return NULL;
        }
        strcat(content, buffer);
        total_size += buffer_len;
    }
    
    content[total_size] = '\0';
    fclose(f);
    free(buffer);

    *httpCode = 200;
    return content;
}
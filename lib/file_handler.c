#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file_handler.h"
#include "log.h"

#define BUFFERSIZE 1024

typedef struct {
    char *ext;
    char *mimetype;
} MimeType;

const MimeType mimetypes[] = {
    {"txt", "text/plain"},
    {"html", "text/html"},
    {"png", "image/png"},
    {"gif", "image/gif"},
    {"jpeg", "image/jpeg"},
    {"jpg", "image/jpg"},
    {"css", "text/css"}};

char *get_file_contents(char *url, int *httpCode){
    FILE *f;
    char *buffer = malloc(BUFFERSIZE);
    char *content = malloc(1);
    content[0] = '\0';
    size_t total_size= 0;
    char path[256]= PATH;

    //Valida que la url no venga vacia, si viene vacia entonces muestra el index
    if (strlen(url) == 0 || strcmp(url, "/") == 0)
    {
        strcat(path, "index.html");
    }
    else
    {
        strcat(path, url);
    }

    //Ahora se abre el archivo solicitado
    
    f = fopen(path, "r");

    if(!f){
        *httpCode = 404;
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
            free(content);
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
char *get_content_type(char *url){

    if (url == NULL || strcmp(url, "/") == 0)
    {
        return mimetypes[1].mimetype;
    }
    log_event(url);
    char *sep = strrchr(url, '.');

    if(sep == NULL){
        return mimetypes[0].mimetype;
    }

    char *ext = sep+1;
    //log_event(ext);
    for (int i =0; i < sizeof(mimetypes)/sizeof(MimeType); i++){
        if(strcmp(mimetypes[i].ext, ext) == 0){

            log_event(mimetypes[i].mimetype);
            return mimetypes[i].mimetype;
        }
    }

    return mimetypes[0].mimetype;
}

unsigned char *get_binary_file_contents(char *url, int *file_size, int *httpCode)
{
    FILE *f;
    unsigned char *buffer;
    char path[256] = PATH;


    // Validar la URL y asignar el index.html si está vacía
    if (strlen(url) == 0 || strcmp(url, "/") == 0)
    {
        strcat(path, "index.html");
    }
    else
    {

        strcat(path, url);

    }
    
    // Intentar abrir el archivo en modo binario
    f = fopen(path, "rb");

    if (!f)
    {
        *httpCode = 404;
        strncpy(path, PATH, sizeof(PATH));
        strcat(path, "index.html");
        f = fopen(path, "rb");

        if (!f)
        {
            log_error("Error al abrir archivo binario");
            return NULL;
        }
    }

    // Obtener el tamaño del archivo
    fseek(f, 0, SEEK_END);
    *file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Reservar espacio para el contenido
    buffer = malloc(*file_size);
    if (buffer == NULL)
    {
        log_error("Error de memoria al leer archivo binario");
        fclose(f);
        return NULL;
    }

    // Leer el contenido completo en el buffer
    size_t read_size = fread(buffer, 1, *file_size, f);
    if (read_size != *file_size)
    {
        log_error("Error al leer el contenido completo del archivo binario");
        free(buffer);
        fclose(f);
        return NULL;
    }

    fclose(f);

    *httpCode = 200;
    return buffer;
}

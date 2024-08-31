#include "log.h"
#include <stdlib.h>
#include <string.h>

void create_log(const char *logfile, const char *message, FILE *stream)
{

    time_t t = time(NULL);

    struct tm tm = *localtime(&t); //Aqui se asignan hora y fecha locales

    //Se asigna memoria para la salida que tendra el log
    char *log_message = malloc(strlen(message) + 100);

    //Al mensaje recibido se le agrega fecha y hora del log
    sprintf(log_message, "[%d-%d-%d %d:%d:%d] %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, message);
    //Se imprime el mensaje en el archivo de log
    fprintf(stream, "%s", log_message);
    free(log_message);
}

void log_event(const char *message)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE *log_file;
    char *log_path = malloc(strlen(LOG_DIRECTORY) + 50);

    sprintf(log_path, "%s%d-%d-%d.txt", LOG_DIRECTORY, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    log_file = fopen(log_path, "a");

    if (log_file == NULL){
        fprintf(stderr, "Error al abrir el archivo de log\n");
        exit(1);
    }

    create_log(log_path, message, log_file);

    fclose(log_file);
    free(log_path);
}

void log_error(const char *message)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE *log_file;
    char *log_path = malloc(strlen(LOG_DIRECTORY) + 50);

    sprintf(log_path, "%s%d-%d-%d-errors.txt", LOG_DIRECTORY, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    log_file = fopen(log_path, "a");

    if (log_file == NULL)
    {
        fprintf(stderr, "Error al abrir el archivo de log\n");
        exit(1);
    }

    create_log(log_path, message, log_file);

    fclose(log_file);
    free(log_path);
}
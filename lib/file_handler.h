#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#define PATH "./html"

char *get_file_contents(char *url, int *httpCode);
char *get_content_type(char *content_type);
unsigned char *get_binary_file_contents(char *url, int *file_size, int *httpCode);

#endif
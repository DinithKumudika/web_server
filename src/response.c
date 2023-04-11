#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/utils.h"

void serve_file(int sock, char *filename, char *fileType)
{
    FILE *file;
    int bytes;
    char header[400];
    char filepath[300];
    char file_name[200];
    char file_type[200];
    // char dir[] = "www/";

    strcpy(file_name, filename);
    strcpy(filepath, SERVER_ROOT);
    strcat(filepath, file_name);

    strcpy(file_type, fileType);

    file = fopen(filepath, "r");

    if (strcmp(file_type, "invalid") == 0)
    {
        sprintf(header, "HTTP/1.1 415 Unsupported Media Type\r\n\r\n");
    }

    // if file not found send 404 page as response and set http response status to 404 Not Found
    if (file == NULL || strcmp(file_name, "404.html") == 0)
    {
        perror("File not found\n");
        file = fopen("www/404.html", "r");
        sprintf(header, "HTTP/1.1 404 Not Found\nContent-Type: %s; charset=utf-8\r\n\r\n", file_type);
    }
    else
    {
        sprintf(header, "HTTP/1.1 200 OK\nContent-Type: %s; charset=utf-8\r\n\r\n", file_type);
    }
    
    get_file_size(file);
    fseek(file, 0L, SEEK_SET);
    char *ptr = malloc(file_size + 1);

    // read file
    size_t size = fread(ptr, 1, file_size, file);
    ptr[size] = 0;

    fclose(file);
    free(ptr);

    write(sock, header, strlen(header));
    send(sock, ptr, file_size, 0);
}
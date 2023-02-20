#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/request.h"
#include "../include/response.h"


void serve_file(int sock, char *filename, char *fileType)
{
    FILE *file;
    int bytes;
    char header[400];
    char filepath[300];
    char file_name[200];
    char file_type[200];
    char dir[] = "www/";

    strcpy(file_name, filename);
    strcpy(filepath, dir);
    strcat(filepath, file_name);

    file = fopen(filepath, "r");



    if (file == NULL)
    {
        file = fopen("www/404.html", "r");
    }

    // get file size
    fseek(file, 0L, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char *ptr = malloc(file_size + 1);
    
    // read file
    size_t size = fread(ptr,1,file_size,file);
    ptr[size] = 0;

    fclose(file);
    free(ptr);

    strcpy(file_type, fileType);
    sprintf(header,"HTTP/1.1 200 OK\nContent-Type: %s\r\n\r\n", file_type);
    write(sock, header, strlen(header));
    send(sock, ptr, file_size, 0);
}
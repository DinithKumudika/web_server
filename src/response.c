#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/utils.h"

// get mime type of the file
char *get_mime_type(char filename[300], mime_type mimeTypes[])
{
    char *ext = strchr(filename, '.');
    if (ext == NULL)
    {
        return "invalid";
    }

    ++ext;

    int len = sizeof(mimeTypes) / sizeof(mimeTypes[0]);

    for (int i = 0; i < len; i++)
    {
        if (strcmp(mimeTypes[i].ext, ext) == 0)
        {
            return mimeTypes[i].type;
        }
    }

    return "invalid";
}


// send response to the client
void send_response(int sock, char *file, char *mime_type)
{
    FILE *ptr_file;
    int bytes;
    char header[400];
    char filepath[300];
    char file_name[200];
    char file_type[200];

    strcpy(file_name, file);
    strcpy(filepath, SERVER_ROOT);
    strcat(filepath, file_name);
    strcpy(file_type, mime_type);

    ptr_file = fopen(filepath, "r");

    // if file not found send 404 page as response and set http response status to 404 Not Found
    if (strcmp(file_type, "invalid") == 0 || ptr_file == NULL)
    {
        perror("File not found\n");
        ptr_file = fopen("www/404.html", "r");
        sprintf(header, HEADER_404);
    }
    else
    {
        sprintf(header, "HTTP/1.1 200 OK\nContent-Type: %s; charset=utf-8\r\n\r\n", file_type);
    }

    get_file_size(ptr_file);
    fseek(ptr_file, 0L, SEEK_SET);
    char *ptr = malloc(file_size + 1);

    // read file
    size_t size = fread(ptr, 1, file_size, file);
    ptr[size] = 0;

    fclose(file);
    free(ptr);

    write(sock, header, strlen(header));
    send(sock, ptr, file_size, 0);
}
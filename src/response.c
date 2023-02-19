#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/constants.h"
#include "../include/response.h"

void serve_file(int sock, char *filename)
{
    FILE *file;
    char buffer[BUFFER_SIZE];
    int bytes;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        sprintf(buffer, "HTTP/1.1 404 Not Found\r\n\r\n");
        send(sock, buffer, strlen(buffer), 0);
    }
    else
    {
        sprintf(buffer, "HTTP/1.1 200 OK\r\n\r\n");
        send(sock, buffer, strlen(buffer), 0);

        while ((bytes = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
        {
            send(sock, buffer, bytes, 0);
        }

        fclose(file);
    }
}
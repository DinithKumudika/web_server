#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "request.h"

int get_request_method(char *buffer)
{
     //char method[10];
     //sscanf(buffer, "%s ", method);
     char *method = strtok(buffer, " ");

     if(strcmp(method, "GET") == 0)
     {
          return REQUEST_METHOD_GET;
     }
     else if(strcmp(method, "POST") == 0)
     {
          return REQUEST_METHOD_POST;
     }
     else
     {
          return REQUEST_METHOD_UNDEFINED; 
     }
}

char *get_request_uri(char *buffer)
{
     char *uri;
     //sscanf(buffer, "%s %s ", &temp, &temp);
     char *ptr = strtok(buffer, " ");
     char *temp = strtok(NULL, " ");


     if(strcmp(temp, "/") == 0)
     {
          strcat(uri, "index.html");
     }
     else if(strcmp(temp, "/about") == 0)
     {
          strcat(uri, "about.html");
     }
     else if(strcmp(temp, "/about") == 0)
     {
          strcat(uri, "contact.html");
     }
     else
     {
          strcat(uri, "404.html");
     }

     return uri;
}

Request *get_request(int socket)
{
     Request *request;
     int msg_len;
     char buffer[REQUEST_SIZE];

     msg_len = recv(socket, buffer, sizeof(buffer), 0);
     printf("Bytes received: %d", msg_len);

     request = (Request *) malloc(sizeof(Request));
     request->type = get_request_method(buffer);
     request->uri = get_request_uri(buffer);
     request->length = msg_len;

     return request;
}
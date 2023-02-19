#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/request.h"

int get_request_method(char method[10])
{

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

char *get_request_file(char uri[300], char filename[300])
{
     
     if(strcmp(uri, "/") == 0)
     {
          strncpy(filename, "www/index.html", 100);
     }
     else if(strcmp(uri, "/about") == 0)
     {
          strncpy(filename, "www/about.html", 100);
     }
     else if(strcmp(uri, "/contact") == 0)
     {
          strncpy(filename, "www/contact.html", 100);
     }
     else
     {
          strncpy(filename, "www/404.html", 100);
     }

     return filename;
}

Request handle_http_request(int sock, char *buffer)
{
     char request_method[10];
     char request_uri[300];
     char request_protocol[128];
     char filename[300];

     Request req;

     sscanf(buffer, "%s %s %s", request_method, request_uri, request_protocol);

     printf("uri : %s\n", request_uri);

     req.type = get_request_method(request_method);
     req.file = get_request_file(request_uri, filename);

     return req;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


#include "../include/constants.h"
#include "../include/request.h"
#include "../include/utils.h"

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
          strcpy(filename, "index.html");
     }
     else if(strcmp(uri, "/about.html") == 0)
     {
          strcpy(filename, "about.html");
     }
     else if(strcmp(uri, "/contact.html") == 0)
     {
          strcpy(filename, "contact.html");
     }
     else if(strcmp(uri, "/flower.jpg") == 0)
     {
          strcpy(filename, "rose.jpg");
     }
     else if(strcmp(uri, "/sample.txt") == 0)
     {
          strcpy(filename, "sample.txt");
     }
     else if(strcmp(uri, "/pikachu.gif") == 0)
     {
          strcpy(filename, "pikachu.gif");
     }
     else if(strcmp(uri, "/styles.css") == 0)
     {
          strcpy(filename, "styles.css");
     }
     else
     {
          strcpy(filename, "404.html");
     }

     return filename;
}

char *get_file_type(char *filename, char fileType[100])
{
     
     if(strstr(filename, ".html") != NULL)
     {
          strcpy(fileType, "text/html");
     }
     else if(strstr(filename, ".jpeg") != NULL || strstr(filename, ".jpg") != NULL)
     {
          strcpy(fileType, "image/jpg");
     }
     else if(strstr(filename, ".txt") != NULL)
     {
          strcpy(fileType, "text/plain");
     }
     else if(strstr(filename, ".gif") != NULL)
     {
          strcpy(fileType, "image/gif");
     }
     else if(strstr(filename, ".css") != NULL)
     {
          strcpy(fileType, "text/css");
     }
     else 
     {
          strcpy(fileType, "invalid");
     }

     return fileType;
}

Request handle_http_request(char *buffer)
{
     char request_method[10];
     char request_uri[300];
     char request_protocol[128];
     char filename[300];
     char fileType[100];

     Request req;

     sscanf(buffer, "%s %s %s", request_method, request_uri, request_protocol);

     printf("uri : %s\n", request_uri);

     req.type = get_request_method(request_method);
     req.file = get_request_file(request_uri, filename);
     req.fileType = get_file_type(req.file, fileType);

     return req;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


#include "../include/constants.h"
#include "../include/request.h"
#include "../include/utils.h"

Methods get_request_method(char *method)
{
     char *method = strtok(req_line, " ");

     if(strcmp(method, "GET") == 0)
     {
          return GET;
     }
     else if(strcmp(method, "HEAD") == 0)
     {
          return HEAD;
     }
     else if(strcmp(method, "POST") == 0)
     {
          return POST;
     }
     else if(strcmp(method, "PUT") == 0)
     {
          return PUT;
     }
     else if(strcmp(method, "PATCH") == 0)
     {
          return PATCH; 
     }
     else if(strcmp(method, "DELETE") == 0)
     {
          return DELETE;
     }
}

float get_http_version(char *http_version)
{
     char *version = strtok(http_version, "/");
     version = strtok(NULL, "/");
     return (float)atof(version);
}

char *get_request_file(char uri[300])
{
     if(strcmp(uri, "/") == 0)
     {
          return "index.html";
     }
     else
     {
          char *filename = strchr(uri, '/');
          ++filename;
          return filename;
     }
}

void handle_http_request(Request request)
{
     
}

Request request_init(char *request_buffer)
{
     char method[10];
     char uri[300];
     char http_version[128];

     for(int i = 0; i < strlen(request_buffer) - 1; i++)
     {
          if (request_buffer[i] == '\n' && request_buffer[i+1] == '\n')
          {
               request_buffer[i+1] = '/';
          }
     }

     // extract request line from request buffer
     char *request_line = strtok(request_buffer, "\n");
     // extract headers from request buffer
     char *request_headers = strtok(NULL, "/");
     // extract body from request buffer
     char *request_body = strtok(NULL,"\n");

     // extract http method, uri and http version from request line
     sscanf(request_line, "%s %s %s", method, uri, http_version);

     Request request;

     request.method = get_request_method(method);
     request.uri = uri;
     request.httpVersion = get_http_version(http_version);

     return req;
}
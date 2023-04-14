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
     else if(strcmp(method, "DELETE") == 0)
     {
          return REQUEST_METHOD_DELETE;
     }
     else if(strcmp(method, "PUT") == 0)
     {
          return REQUEST_METHOD_PUT;
     }
     else
     {
          return REQUEST_METHOD_UNDEFINED; 
     }
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

// get mime type of the file
char *get_mime_type(char filename[300], mime_type mimeTypes[])
{
     char *ext = strchr(filename, '.');
     if(ext == NULL)
     {
          return "invalid";
     }

     ++ext;

     int len =  sizeof(mimeTypes) / sizeof(mimeTypes[0]);

     for(int i = 0; i< len; i++)
     {
          if(strcmp(mimeTypes[i].ext, ext) == 0)
          {
               return mimeTypes[i].type;
          }
     }

     return "invalid";
}

void handle_http_request()
{

}

Request request_init(char *request_buffer)
{
     char method[10];
     char uri[300];
     char http_version[128];

     Request req;

     for(int i = 0; i < strlen(request_buffer) - 1; i++)
     {
          
     }

     // get request line from request buffer
     char *request_line = strtok(request_buffer, "\n");
     // extract http method, uri and http version from request line
     sscanf(request_line, "%s %s %s", method, uri, http_version);

     printf("method : %s\n", method);
     printf("uri : %s\n", uri);
     printf("http version : %s\n", http_version);

     req.httpMethod = get_request_method(method);
     req.uri = uri;
     req.httpVersion = http_version;

     return req;
}
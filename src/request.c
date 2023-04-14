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

Request handle_http_request(char *buffer)
{
     char request_method[10];
     char request_uri[300];
     char request_protocol[128];

     Request req;

     sscanf(buffer, "%s %s %s", request_method, request_uri, request_protocol);

     printf("uri : %s\n", request_uri);

     req.type = get_request_method(request_method);
     req.file = get_request_file(request_uri);
     req.fileType = get_mime_type(req.file, mime_type mimeTypes[]);

     return req;
}
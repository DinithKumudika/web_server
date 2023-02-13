#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "request.h"

int get_request_method(char *req_line)
{
     char method[10] = {0};
     sscanf(req_line, "%s ", method);

     if(strcmp(method, "GET") == 0)
     {
          return GET;
     }
     else if(strcmp(method, "POST") == 0)
     {
          return POST;
     }
     else
     {
          return REQUEST_UNDEFINED; 
     }
}

char *get_request_uri(char *req_line)
{
     char temp[100] = {0};
     sscanf(req_line, "%s %s ", temp);

     char uri[] = temp[strlen(temp) -1];

     if(uri == "/")
     {
          strcat(temp, "index.html");
     }
     else if(uri == "/about")
     {
          strcat(temp, "about.html");
     }
     else if(uri == "/contact")
     {
          strcat(temp, "contact.html");
     }
     else
     {
          strcat(temp, "404.html");
     }

     return strdup(temp);
}

Request *get_request(int sock)
{
     Request *request;
     int msg_len;
     char buffer[REQUEST_SIZE];

     msg_len = recv(sock, buffer, sizeof(buffer), 0);
     printf("Bytes received: %d", msg_len);

     request = malloc(sizeof(Request));
     request->type = get_request_method(buffer);
     request->uri = get_request_uri(buffer);
     request->length = msg_len;

     return request;
}
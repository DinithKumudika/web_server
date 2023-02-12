#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "request.h"

int get_request_method(char *buffer)
{
     char retval[10] = {0};
     sscanf(buffer, "%s ", retval);

     if(strcmp(retval, "GET") == 0)
     {
          return GET;
     }
     else if(strcmp(retval, "POST") == 0)
     {
          return POST;
     }
     else
     {
          return REQUEST_UNDEFINED; 
     }
}

char *get_request_uri(char *buffer)
{
     char retval[100] = {0};
     sscanf(buffer, "%s %s ", retval);

     char uri[] = retval[strlen(retval) -1];

     if(uri == "/")
     {
          strcat(retval, "index.html");
     }
     else if(uri == "/about")
     {
          strcat(retval, "about.html");
     }
     else if(uri == "/contact")
     {
          strcat(retval, "contact.html");
     }
     else
     {
          strcat(retval, "404.html");
     }

     char *target = strdup(retval);

     return target;
}
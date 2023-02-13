#include <stdio.h>

typedef struct Request 
{
     int type;
     char *uri;
     int length;
} Request;

int get_request_method(char *buffer);
char *get_request_uri(char *buffer);
Request *get_request(int sock);


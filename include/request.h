#include <sys/types.h>


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "constants.h"

typedef struct Request 
{
     int method;
     char *uri;
     float httpVersion;
} Request;

Methods get_request_method(char *method);
float get_http_version(char *http_version);
char *get_request_file(char uri[300]);

Request request_init(char *request_buffer);
void handle_http_request(Request request);



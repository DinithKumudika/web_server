#include <sys/types.h>


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

typedef struct Request 
{
     int method;
     char *uri;
     float httpVersion;
} Request;

typedef struct mime_type {
     char *ext;
     char *type;
} mime_type;

mime_type mimeTypes[] = {
     {
          "htm", 
          "text/html"
     },
     {
          "html", 
          "text/html"
     },
     {
          "css", 
          "text/css"
     },
     {
          "jpg", 
          "image/jpeg"
     },
     {
          "jpeg", 
          "image/jpeg"
     },
     {
          "png", 
          "image/png"
     },
     {
          "gif", 
          "image/gif"
     },
     {
          "txt", 
          "text/plain"
     },
     {
          "js", 
          "application/x-javascript"
     }
};


int get_request_method(char method[10]);
char *get_request_file(char uri[300]);
char *get_mime_type(char filename[300], mime_type mimeTypes[]);

Request request_init(char *request_buffer);



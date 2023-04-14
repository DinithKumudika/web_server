#include <sys/types.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

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

typedef struct Response {
     char *mimeType;
     char *headers;
     char *body;
}Response;

char *get_mime_type(char filename[300], mime_type mimeTypes[]);
void send_response(int sock, char *filename, char *fileType);
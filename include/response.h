#include <sys/types.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

typedef struct Response {
     char *mimeType;
     char *headers;
     char *body;
}Response;


void serve_file(int sock, char *filename, char *fileType);
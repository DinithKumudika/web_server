#include <sys/types.h>


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

typedef struct Request 
{
     int type;
     char *file;
     char *fileType;
} Request;

int get_request_method(char method[10]);
char *get_request_file(char uri[300], char filename[300]);
char *get_file_type(char *filename, char fileType[100]);

Request handle_http_request(char *buffer);



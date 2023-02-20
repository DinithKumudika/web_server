#include <sys/types.h>


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>


typedef struct Server
{
     int domain;
     int protocol;
     int socket_type;
     unsigned long host_interface;
     int port;
     int backlog;

     struct sockaddr_in address;
     int socket;
} Server;

Server server_init(int domain, int protocol, int socket_type, unsigned long host_interface, int port, int backlog);

void launch(Server *server);
#include <sys/types.h>
#include "constants.h"

#ifdef _WIN32
     #include <winsock.h>
     #include <WS2tcpip.h>
     #include <WS2spi.h>
     #define HOST_OS HOST_OS_WIN
#elif __linux__
     #include <unistd.h>
     #include <sys/socket.h>
     #include <netinet/in.h>
     #include <netinet/tcp.h>
     #include <arpa/inet.h>
     #define HOST_OS HOST_OS_LINUX
#endif

typedef struct Server
{
     int domain;
     int protocol;
     int service;
     unsigned long net_interface;
     int port;
     int backlog;

     struct sockaddr_in address;
     int socket;
} Server;

Server server_init(int domain, int protocol, int service, unsigned long net_interface, int port, int backlog);

void launch(Server *server);
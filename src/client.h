#include <sys/types.h>

#ifdef _WIN32
     #include <winsock2.h>
     #include <WS2tcpip.h>
     #include <WS2spi.h>
     #include <Windows.h>
     #define HOST_OS "windows"
#elif __linux__
     #include <unistd.h>
     #include <sys/socket.h>
     #include <netinet/in.h>
     #include <netinet/tcp.h>
     #include <arpa/inet.h>
     #define HOST_OS "linux"
#endif

typedef struct Client
{
     int domain;
     int protocol;
     int service;
     unsigned long net_interface;
     int port;
     int backlog;

     struct sockaddr_in address;
     int socket;
} Client;

void client_init(Server server);
#include <sys/types.h>

#ifdef _WIN32
     #include <winsock.h>
     #include <WS2tcpip.h>
     #include <WS2spi.h>
     #define HOST_OS "windows"
     #define _WIN32_WINNT 0x601
#elif __linux__
     #include <sys/socket.h>
     #include <netinet/in.h>
     #include <arpa/inet.h>
     #define HOST_OS "linux"
#endif

struct Server
{
     int domain;
     int protocol;
     int service;
     u_long net_interface;
     int port;
     int backlog;

     struct sockaddr_in address;
     int socket;

     void (*launch)(void);
};

struct Server server_constructor(int domain, int protocol, int service, u_long net_interface, int port, int backlog, void (*launch)(void));




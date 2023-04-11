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
     #include <pthread.h>
     #include <semaphore.h>
     #define HOST_OS "linux"
#endif

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

// TODO:implement socket_thread function
void *socket_thread(void *arg);
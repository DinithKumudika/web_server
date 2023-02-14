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

typedef struct Request 
{
     int type;
     char *uri;
     int length;
} Request;

int get_request_method(char *buffer);
char *get_request_uri(char *buffer);
Request *get_request(int socket);


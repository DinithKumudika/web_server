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
     char *file;
} Request;

int get_request_method(char method[10]);
char *get_request_file(char uri[300]);

Request handle_http_request(int sock, char *buffer);



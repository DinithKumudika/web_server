#define SERVER_ROOT "../www"
#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024
#define _WIN32_WINNT 0x601
#define REQUEST_SIZE 4096

#define REQUEST_METHOD_UNDEFINED 0
#define REQUEST_METHOD_GET 1
#define REQUEST_METHOD_POST 2

#define HEADER_200 "HTTP/1.0 200 OK\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n"
#define HEADER_400 "HTTP/1.0 400 Bad Request\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n"
#define HEADER_404 "HTTP/1.0 404 Not Found\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n"

// enum {
//      REQUEST_UNDEFINED,
//      GET,
//      POST
// } REQUEST_METHODS;
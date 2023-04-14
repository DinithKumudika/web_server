#define SERVER_ROOT "www/"
#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024
#define _WIN32_WINNT 0x601
#define REQUEST_SIZE 4096
#define THREAD_POOL_SIZE 30

enum http_methods {
     GET,
     HEAD,
     POST,
     PUT,
     PATCH,
     DELETE
};

#define HEADER_200 "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\r\n\r\n"
#define HEADER_400 "HTTP/1.1 404 Bad Request\nContent-Type: text/html; charset=utf-8\r\n\r\n"
#define HEADER_404 "HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=utf-8\r\n\r\n"
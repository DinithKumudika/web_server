#define SERVER_ROOT "../www"
#define DEFAULT_PORT 80
#define HOST_OS_WIN "windows"
#define HOST_OS_LINUX "linux"
#define _WIN32_WINNT 0x601

enum {
     REQUEST_UNDEFINED,
     GET,
     POST
} REQUEST_METHODS;
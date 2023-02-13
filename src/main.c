#include "constants.h"
#include "server.h"
#include "request.h"

// https://bruinsslot.jp/post/simple-http-webserver-in-c/ 
// https://dev-notes.eu/2018/06/http-server-in-c/

int main()
{
     Server server = server_init(AF_INET, 0, SOCK_STREAM, INADDR_ANY, DEFAULT_PORT, SOMAXCONN);
     launch(&server);
     
     return 0;
}
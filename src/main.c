#include "../include/constants.h"
#include "../include/server.h"

// https://bruinsslot.jp/post/simple-http-webserver-in-c/ 

int main()
{
     Server server = server_init(AF_INET, 0, SOCK_STREAM, INADDR_ANY, DEFAULT_PORT, SOMAXCONN);
     launch(&server);
     
     return 0;
}
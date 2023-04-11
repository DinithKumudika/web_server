#include "../include/constants.h"
#include "../include/server.h"

// https://bruinsslot.jp/post/simple-http-webserver-in-c/ 

int main(int argc, char* argv[])
{
     if(argc < 2)
     {
          const int PORT = DEFAULT_PORT;
     }
     else
     {
          const int PORT = atoi(argv[1]);
     }
     
     // initialize server and return server struct
     Server server = server_init(AF_INET, 0, SOCK_STREAM, INADDR_ANY, PORT, SOMAXCONN);
     // launch server and start accepting connections from clients
     launch(&server);
     
     return 0;
}
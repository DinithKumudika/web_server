#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/server.h"

// thread id's in thread pool
pthread_t threads[THREAD_POOL_SIZE];

// thread safety
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int main(int argc, char *argv[])
{
     // get port to run the server through command line arguments
     if (argc < 2)
     {
          printf("no port provided. using default port %d", DEFAULT_PORT);
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
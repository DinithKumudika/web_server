#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/server.h"

// thread id's in thread pool
pthread_t threads[THREAD_POOL_SIZE];

// thread safety
// initialize mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

int main(int argc, char *argv[])
{
     // runs server on user provided port or default port 8080
     while (opt = getopt(argc, argv, "p:") != -1)
     {
          switch (opt)
          {
          case 'p':
               if (optarg != NULL)
               {
                    const int PORT = atoi(optarg);
                    break;
               }
               else
               {
                    printf("option -%c requires the port as an argument (ex-: -p 8000).\n", optopt);
                    continue;
               }
          case '?':
               printf("unknown option. usage: bin/server [-p port]\n");
               break;
          default:
               printf("no port provided. using default port %d\n", DEFAULT_PORT);
               const int PORT = DEFAULT_PORT;
               break;
          }
     }

     // initialize server and return server struct
     Server server = server_init(AF_INET, 0, SOCK_STREAM, INADDR_ANY, PORT, SOMAXCONN);

     // launch server and start accepting connections from clients
     launch(&server);

     return 0;
}
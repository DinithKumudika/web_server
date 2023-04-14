#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/utils.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/server.h"

#include "../libs/queue/queue.h"

// initialize server and return server struct
Server server_init(int domain, int protocol, int socket_type, unsigned long host_interface, int port, int backlog)
{
     Server server;

     server.domain = domain;
     server.protocol = protocol;
     server.socket_type = socket_type;
     server.host_interface = host_interface;
     server.port = port;

     // number of the pending connections will be queued up to accept
     server.backlog = backlog;

     // create a server socket
     server.socket = socket(server.domain, server.socket_type, server.protocol);

     if (server.socket < 0)
     {
          // print failed to connect error message
          perror("Failed to create socket\n");
          exit(1);
     }

     /* local address configuration */

     // set communication domain
     server.address.sin_family = server.domain;
     // htons(value) - convert short integer from host byte order to TCP/IP network byte order
     server.address.sin_port = htons(server.port);
     // htonl(value) - convert long integer from host byte order to TCP/IP network byte order
     server.address.sin_addr.s_addr = htonl(server.host_interface);

     // assign ip address to the socket
     int bind_status = bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address));

     if (bind_status < 0)
     {
          perror("Failed to bind socket\n");
          exit(1);
     }

     printf("Server started on port %d\n", DEFAULT_PORT);

     // listening for incoming connections
     int listening_status = listen(server.socket, server.backlog);

     if (listening_status < 0)
     {
          perror("Failed to listen to the connection\n");
          exit(1);
     }

     printf("Server is listening on port %d\n", DEFAULT_PORT);

     return server;
}

// thread function
void *handle_socket_thread(void *arg)
{
     // runs the thread on a infinite loop
     while (1)
     {
          pthread_mutex_lock(&mutex);
          pthread_cond_wait(&cond_var, &mutex);
          int *ptr_client_socket = dequeue();
          pthread_mutex_unlock(&mutex);

          // handle client connection if deque has returned a client socket
          if (ptr_client_socket != NULL)
          {
               handle_connection(ptr_client_socket);
          }
     }
}

// handle a http connection from a client
void handle_connection(int *ptr_client_socket) 
{
     char buffer[BUFFER_SIZE];
     int client_socket = *(ptr_client_socket);
     free(ptr_client_socket);
     memset(buffer, 0, BUFFER_SIZE);

     int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);

     if (bytes_received < 0)
     {
          perror("Failed to read incoming request\n");
          continue;
     }

     printf("Bytes received : %d\n", bytes_received);
     printf("buffer : %s\n", buffer);

     // handle request
     Request request = request_init(buffer);

     printf("method : %d\n", request.method);
     printf("uri : %s\n", request.uri);
     printf("HTTP version: %.2f\n", request.httpVersion);

     handle_http_request(request);

     send_response(client_socket, request.file, request.fileType);

     close(client_socket);
}

// launch the server and accept incoming connections and read from and write to connections
void launch(Server *server)
{
     int sock;
     socklen_t addr_len = sizeof(server->address);

     // create queue and allocate memory
     queue queue;
     memset(&queue, 0, sizeof(queue));

     // create a fixed no of threads to handle connections
     for (int i = 0; i < THREAD_POOL_SIZE; i++)
     {
          thread_status = pthread_create(&threads[i], NULL, &handle_socket_thread, NULL);

          if (thread_status < 0)
          {
               perror("Failed to create thread %d\n", i + 1);
          }
     }

     while (1)
     {
          printf("Waiting for connection...\n");

          // accept a incoming connection and create a new connected socket for the connection
          sock = accept(server->socket, (struct sockaddr *)&server->address, &addr_len);

          if (sock < 0)
          {
               perror("Failed to accept the connection\n");
               continue;
          }

          int *ptr_sock = (int *)malloc(sizeof(int));
          *ptr_sock = sock;

          pthread_mutex_lock(&mutex);
          // add client socket of current connection to the queue so available threads can use them
          enqueue(&queue, ptr_sock);
          pthread_cond_signal(&cond_var);
          pthread_mutex_unlock(&mutex);
     }

     pthread_exit(NULL);

     // shutdown socket connection
     shutdown(server->socket, SD_BOTH);
     close(server->socket);
}

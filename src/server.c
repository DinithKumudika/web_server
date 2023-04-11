#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/server.h"


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

// launch the server and accept incoming connections and read from and write to connections
void launch(Server *server)
{
     char buffer[BUFFER_SIZE];
     int sock;
     socklen_t addr_len = sizeof(server->address);

     pthread_t tid[60];
     int i = 0;

     while (1)
     {
          printf("Waiting for connection...\n");
          
          // accept a incoming connection and create a new connected socket for the connection
          sock = accept(server->socket, (struct sockaddr *)&server->address, &addr_len);

          // create a thread of every client request and assign client request to the process
          int thread_status = pthread_create(&tif[i++], NULL, socket_thread, &sock);
          if(thread_status < 0)
          {
               perror("Failed to create thread\n");
          }

          if (sock < 0)
          {
               perror("Failed to accept the connection\n");
               continue;
          }

          memset(buffer, 0, BUFFER_SIZE);

          int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);

          if(bytes_received<0)
          {
               perror("Failed to read incoming request\n");
               continue;
          }

          printf("Bytes received : %d\n", bytes_received);
          printf("buffer : %s\n", buffer);

          Request request = handle_http_request(sock, buffer);

          printf("method : %d\n", request.type);
          printf("requested file : %s\n", request.file);
          printf("requested file type: %s\n", request.fileType);


          serve_file(sock, request.file, request.fileType);

          close(sock);
     }
}

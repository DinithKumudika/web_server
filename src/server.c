#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "constants.h"
#include "server.h"

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

     // listening for incoming connections
     int listening_status = listen(server.socket, server.backlog);

     if (listening_status < 0)
     {
          perror("Failed to listen to the connection\n");
          exit(1);
     }

     return server;
}

// launch the server and accept incoming connections and read from and write to connections
void launch(Server *server)
{
     char buffer[BUFFER_SIZE];
     int sock;
     socklen_t addr_len = sizeof(server->address);

     char resp[] = "HTTP/1.0 200 OK\r\nServer: webserver-c\r\nContent-type: text/html\r\n\r\n<html>hello, world</html>\r\n";

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

          if(read(sock, buffer, BUFFER_SIZE)<0)
          {
               perror("Failed to read incoming request\n");
               continue;
          }
          
          printf("buffer : %s\n", buffer);
          
          if(write(sock, resp, strlen(resp)) < 0)
          {
               perror("Failed to write to request\n");
               continue;
          } 
          close(sock);
     }
}

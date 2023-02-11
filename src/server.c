#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "constants.h"

// https://bruinsslot.jp/post/simple-http-webserver-in-c/

struct Server server_init(int domain, int protocol, int service, u_long net_interface, int port, int backlog)
{
     Server server;

     server.domain = domain;
     server.protocol = protocol;
     server.service = service;
     server.net_interface = net_interface;
     server.port = port;
     server.backlog = backlog;

     /* local address configuration */

     // set communication domain
     server.address.sin_family = server.domain;
     // htons(value) - convert short integer from host byte order to TCP/IP network byte order
     server.address.sin_port = htons(server.port);
     // htonl(value) - convert long integer from host byte order to TCP/IP network byte order
     server.address.sin_addr.s_addr = htonl(server.net_interface);

     // create a server socket
     server.socket = socket(server.domain, server.service, server.protocol);

     if (server.socket == 0)
     {
          // print failed to connect error message
          perror("Failed to connect socket\n");
          exit(1);
     }

     // bind socket to the address - assign server address to the socket
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

void launch(Server *server)
{
     while (1)
     {
          char buffer[30000];
          printf("Waiting for connection...\n");

          socklen_t addr_len = sizeof(server->address);
          // accept incoming connection and create a new socket for the connection
          int soc = accept(server->socket, (struct sockaddr *)&server->address, &addr_len);

          if (soc < 0)
          {
               perror("Failed to accept the connection\n");
               exit(1);
          }

          read(soc, buffer, 30000);
          printf("buffer : %s\n", buffer);

          close(soc);
     }
}

int main()
{
     Server server = server_init(AF_INET, 0, SOCK_STREAM, INADDR_ANY, DEFAULT_PORT, 50);
     launch(&server);
     return 0;
}

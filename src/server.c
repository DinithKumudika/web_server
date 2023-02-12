#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "constants.h"

// https://bruinsslot.jp/post/simple-http-webserver-in-c/

Server server_init(int domain, int protocol, int service, unsigned long net_interface, int port, int backlog)
{
     Server server;

     server.domain = domain;
     server.protocol = protocol; 
     server.service = service;
     server.net_interface = net_interface;
     server.port = port;
     // maximum length of teh pending connections queue
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

     if (server.socket < 0)
     {
          // print failed to connect error message
          perror("Failed to connect socket\n");
          exit(1);
     }

     // bind ip address and port to the socket
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
     char buffer[30000];
     int soc;
     socklen_t addr_len = sizeof(server->address);

     char *hello = "HTTP/1.1 200 OK\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed\n\n
          <html><body><h1>Testing ...</h1></body></html>";

     while (1)
     {
          printf("Waiting for connection...\n");
          
          // accept incoming connection and create a new socket for the connection
          soc = accept(server->socket, (struct sockaddr *)&server->address, &addr_len);

          if (soc < 0)
          {
               perror("Failed to accept the connection\n");
               exit(1);
          }

          read(soc, buffer, 30000);
          printf("buffer : %s\n", buffer);
          
          write(soc, hello, strlen(hello));
          close(soc);
     }
}

int main()
{
     Server server = server_init(AF_INET, 0, SOCK_STREAM, INADDR_ANY, DEFAULT_PORT, 50);
     launch(&server);
     return 0;
}

#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Server server_constructor(int domain, int protocol, int service, u_long net_interface, int port, int backlog, void (*launch)(void))
{
     struct Server server;

     server.domain = domain;
     server.protocol = protocol;
     server.service = service;
     server.net_interface = net_interface;
     server.port = port;
     server.backlog = backlog;

     server.address.sin_family = domain;
     // htons(value) - convert short integer from host byte order to TCP/IP network byte order
     server.address.sin_port = htons(port);
     // htonl(value) - convert long integer from host byte order to TCP/IP network byte order
     server.address.sin_addr.s_addr = htonl(net_interface);

     server.socket = socket(domain, service, protocol);

     return server;
}


int main()
{
     return 0;
}

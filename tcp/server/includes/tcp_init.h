#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#ifndef _TCP_INIT_H    /* Guard against multiple inclusion */
#define _TCP_INIT_H

#define LISTEN_BACKLOG 50

#define SERVER_IP "192.168.1.230"
#define SERVER_PORT 1988

extern int tcp_socket;
extern struct sockaddr_in peer_addr;

int init_tcp(void);

#endif

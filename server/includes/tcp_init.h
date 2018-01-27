#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define LISTEN_BACKLOG 50

int init_tcp(void);

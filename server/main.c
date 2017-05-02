#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init_tcp.h"

int main(){
    int tcp_socket;
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(struct sockaddr_in);

    //--------------------------------------------------------------------------
    // init TCP socket
    //--------------------------------------------------------------------------
    tcp_socket = init_tcp();
    if( tcp_socket < 0 ){
        return -1;
    }

    //--------------------------------------------------------------------------
    // waiting for connections
    //--------------------------------------------------------------------------
    printf("Listening and accepting incoming TCP socket connections. Press Ctrl+C to exit\n");
    int incoming_socket = accept(tcp_socket, (struct sockaddr *) &peer_addr, &peer_addr_size);
    if( incoming_socket < 0 ){
        switch(errno){
            case EBADF: fprintf(stderr, "tcp_socket is not an open file descriptor\n");break;
            case ENOTSOCK: fprintf(stderr, "The file descriptor tcp_socket does not refer to a socket.\n");break;
            default: fprintf(stderr, "Something went wrong with socket accepting, the error code is %i\n", errno);break;
        }
        return -1;
    }

    char buffer[500];
    while( 1 ){
        int len = read(incoming_socket, buffer, 500, 0);
        if(len < 0){
            switch(errno){
                case EAGAIN: fprintf(stderr, "The socket is marked nonblocking and the receive operation...\n");break;
                case EBADF: fprintf(stderr, "The argument sockfd is an invalid file descriptor.\n");break;
                case ECONNREFUSED: fprintf(stderr, "A remote host refused to allow the network connection (typically because it is not running the requested service).\n");break;
                case EFAULT: fprintf(stderr, "The receive buffer pointer(s) point outside the process's address space.\n");break;
                case EINTR: fprintf(stderr, "he receive was interrupted by delivery of a signal before any data were available;\n");break;
                case EINVAL: fprintf(stderr, "Invalid argument passed.\n");break;
                case ENOMEM: fprintf(stderr, "Could not allocate memory for recvmsg().\n");break;
                case ENOTCONN: fprintf(stderr, "The socket is associated with a connection-oriented protocol and has not been connected\n");break;
                case ENOTSOCK: fprintf(stderr, "The file descriptor sockfd does not refer to a socket.\n");break;
                default: fprintf(stderr, "Something went wrong with receiving messages, the error code is %i\n", errno);break;
            }
            return -1;
        }
        printf("Incoming message: %s\n", buffer);
    }

    return 0;
}

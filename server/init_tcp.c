#include "init_tcp.h"

int init_tcp(){
    struct sockaddr_in server_address;

    //--------------------------------------------------------------------------
    // creating the socket
    //--------------------------------------------------------------------------
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0|IPPROTO_TCP);
    if(tcp_socket < 0){
        switch(errno){
            case EACCES: fprintf(stderr, "Permission to create a socket of the specified type and/or protocol is denied.\n"); break;
            default: fprintf(stderr, "Something went wrong with socket creation, the error code is %i\n", errno);break;
        }
        close(tcp_socket);
        return -1;
    }

    //--------------------------------------------------------------------------
    // binding the socket to a local address
    //--------------------------------------------------------------------------
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2017);
    inet_aton("192.168.1.7", &server_address.sin_addr);

    if(bind(tcp_socket,(struct sockaddr *) &server_address, sizeof(struct sockaddr_in)) < 0){
        switch(errno){
            case EACCES: fprintf(stderr, "Permission to create a socket of the specified type and/or protocol is denied.\n"); break;
            case EADDRINUSE: fprintf(stderr, "The given address for binding is already in use.\n"); break;
            default: fprintf(stderr, "Something went wrong with socket binding, the error code is %i\n", errno);break;
        }
        close(tcp_socket);
        return -1;
    }

    //--------------------------------------------------------------------------
    // put socket into listening state
    //--------------------------------------------------------------------------
    if( listen(tcp_socket, LISTEN_BACKLOG) < 0){
        switch(errno){
            case EADDRINUSE: fprintf(stderr, "Another socket is already listening on the same port.\n"); break;
            default: fprintf(stderr, "Something went wrong with socket listening, the error code is %i\n", errno);break;
        }
        close(tcp_socket);
        return -1;
    }

    return tcp_socket;
}

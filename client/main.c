#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>


int main(){
    struct sockaddr_in server_address;
    socklen_t peer_addr_size = sizeof(struct sockaddr_in);

    //--------------------------------------------------------------------------
    // creating the socket
    //--------------------------------------------------------------------------
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket < 0){
        switch(errno){
            case EACCES: fprintf(stderr, "Permission to create a socket of the specified type and/or protocol is denied.\n"); break;
            default: fprintf(stderr, "Something went wrong with socket creation, the error code is %i\n", errno);break;
        }
        return -1;
    }

    //--------------------------------------------------------------------------
    // create addr sstruct to where to connect
    //--------------------------------------------------------------------------
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1988);

    inet_aton("192.168.1.7", &server_address.sin_addr);

    //--------------------------------------------------------------------------
    // connect to the address spcified above
    //--------------------------------------------------------------------------
    if( connect(tcp_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in)) < 0 ){
        switch(errno){
            case EACCES: fprintf(stderr, "The address is protected, and the user is not the superuser.\n");break;
            case EADDRINUSE: fprintf(stderr, "The given address is already in use.\n");break;
            case ECONNREFUSED: fprintf(stderr, "No-one listening on the remote address.\n");break;
            default: fprintf(stderr, "Something went wrong with socket accepting, the error code is %i\n", errno);break;
        }
        return -1;
    } else {
        printf("Connected OHH YEAH\n");
    }

    printf("Type \"exit\" to exit or any other message to send\n");
    char buf[500];
    char c;
    int i;
    while(1){
        i=0;
        while(1){
            c = getchar();
            if(c == '\n') break;
            buf[i] = c;
            i++;
        }
        if( strcmp(buf, "exit") == 0){
            return 0;
        }
        if( send(tcp_socket, buf, strlen(buf) + 1, 0) < 0){
            switch(errno){
                default: fprintf(stderr, "Something went wrong with sending message, the error code is %i\n", errno);break;
            }
            return -1;
        }
        memset(&buf, 0, sizeof(buf));
    }

    return 0;
}

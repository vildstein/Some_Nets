#ifndef TCP_SERVER_FUNC_H
#define TCP_SERVER_FUNC_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL

SOCKET tcp_server (char* hostName, char* portName) {

    struct sockaddr_in local;
    SOCKET socket;

    const int on = 1;

    set_address( hostName, portName, &local, "tcp" );

    socket = ( AF_INET, SOCK_STREAM, 0 );

    if (!IS_VALID_SOCKET( socket )) {
        error( 1, errno, "SOCKET FUNC MISTAKE");
    }

    if ( setsockopt( socket, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof(on)) ) {
        error( 1, errno, "SET_SOCKET_OTP FUNC MISTAKE");
    }

    if ( bind ( socket, (struct sockaddr*) &local, sizeof(local)) ) {
        error( 1, errno, "BIND FUNC MISTAKE");
    }

    if ( listen( socket, NLISTEN) ) {
        error( 1, errno, "LISTEN FUNC MISTAKE");
    }

    return socket;
}

#endif //TCP_SERVER_FUNC_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL
SERVER_FUNC_FORWARD_DECL

int main( int argc, char** argv) {

    struct sockaddr_in local;
    struct sockaddr_in peer;

    char* hostName = DEFAULT_HOST;
    char* portNumber = DEFAULT_PORT;
    char* protocol = DEFAULT_NETWORK_PROTOCOL;

    SOCKET sock1;
    SOCKET s;

    const int on = 1;

    INIT();

    if (argc == 3) {
        hostName = argv[ 1 ];
        portNumber = argv[ 2 ];
    } else if (argc == 2) {
        hostName = NULL;
        portNumber = argv[ 1 ];
    } else if (argc = 1) {
        hostName = NULL;
        portNumber = "9000";
    } else {
        puts("NO HOST ADDRESS WAS PROVIDED. EXIT.\n");
        EXIT(1);
    }

    set_address( hostName, portNumber, &local, "tcp" ); //Check this

    s = socket(AF_INET, SOCK_STREAM, 0 );

    if (!IS_VALID_SOCKET(s)) {
        error(1, errno, "SOCKET FUNC FAILURE");
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) {
        error(1, errno, "SET_SOCK_OPT FUNC FAILURE");
    }

    if ( bind( s, (struct sockaddr*) &local, sizeof(local)) ) {
        error(1, errno, "BIND FUNC FAILURE");
    }

    if (listen(s, NLISTEN)) {
        error(1, errno, "LISTEN FUNC FAILURE");
    }

    int peerLen;

    do {
        peerLen = sizeof(peer);
        sock1 = accept( s, (struct sockaddr*) &peer, &peerLen);
        if (!IS_VALID_SOCKET(sock1) ) {
            error(1, errno, "ACCEPT FUNCTION FAIL");
        }

        server(sock1, &peer);
        CLOSE( sock1 );

    } while (TRUE);

    EXIT(0);
}

static void server(SOCKET s, SIN* peer) {
    char* answer =  {"TCP Serv Skeleton Answer\n\n\n"};
    send(s, answer, strlen(answer), 0);
}

static void ans(SOCKET s, const char* ans) {
    char* answer =  ans;
    send(s, answer, strlen(answer), 0);
}
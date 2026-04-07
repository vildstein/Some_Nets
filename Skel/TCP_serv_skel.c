#include "skel_defines.h"

ERROR_FORWARD_DECL
SERVER_FUNC_FORWARD_DECL
TCP_SERVER_FORWARD

int main( int argc, char** argv) {

    struct sockaddr_in local;
    struct sockaddr_in peer;

    char* hostName = DEFAULT_HOST;
    char* portNumber = DEFAULT_PORT;
    char* protocol = DEFAULT_NETWORK_PROTOCOL;

    SOCKET answeringSocket;
    SOCKET listeningSocket;

    const int on = 1;

    INIT();

    if (argc == 3) {
        hostName = argv[ 1 ];
        portNumber = argv[ 2 ];
        puts("(argc = 3");
    } else if (argc == 2) {
        hostName = NULL;
        portNumber = argv[ 1 ];
        puts("argc = 2");
    } else if (argc = 1) {
        hostName = NULL;
        portNumber = "9000";
        puts("argc = 1");
    } else {
        puts("NO HOST ADDRESS WAS PROVIDED. EXIT.\n");
        EXIT(1);
    }

    listeningSocket = tcp_server(hostName, portNumber);

    int peerLen;

    do {
        peerLen = sizeof(peer);
        answeringSocket = accept( listeningSocket, (struct sockaddr*) &peer, &peerLen);
        if (!IS_VALID_SOCKET(answeringSocket) ) {
            error(1, errno, "ACCEPT FUNCTION FAIL");
        }

        server(answeringSocket, &peer);
        CLOSE( answeringSocket );

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
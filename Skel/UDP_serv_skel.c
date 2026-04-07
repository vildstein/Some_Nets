#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL
//SERVER_FUNC_FORWARD_DECL

static void server(SOCKET s, SIN* local);


int main( int argc, char** argv) {

    struct sockaddr_in local;

    char* hostName = DEFAULT_HOST;
    char* portNumber = DEFAULT_PORT;
    char* protocol = {"udp"};

    SOCKET sock;

    // const int on = 1;

    INIT();

    switch(argc) {
    case 1:
        puts("NO HOST ADDRESS OR PORT WAS PROVIDED. EXIT.\n");
        EXIT(1);
    case 2:
        hostName = "127.0.0.1";
        portNumber = argv[1];
        break;
    case 3:
        hostName = argv[1];
        portNumber = argv[2];
        break;
    default:
        break;
    };

    set_address( hostName, portNumber, &local, protocol );

    sock = socket( AF_INET, SOCK_DGRAM, 0 );

    if ( !IS_VALID_SOCKET(sock) ) {
        error(1, errno, "SOCKET FUNCTION MISTAKE");
    }

    if ( bind( sock, (struct sockaddr* ) &local, sizeof(local) ) ) {
        error(1, errno, "BIND FUNCTION MISTAKE");
    }

    server(sock, &local);

    EXIT(0);
}

static void server(SOCKET s, SIN* local) {
    struct sockaddr_in peer;
    int peerlen;
    char buffer[1];

    char message[] = "hello world FUCK OFF Maza Faka\n";

    for (;;) {
        peerlen = sizeof(peer);
        if ( recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr*) &peer, &peerlen) < 0 ) {
            error(1, errno, "RECVFROM FUNCTION MISTAKE");
        }

        if (sendto(s, message, sizeof(message), 0, (struct sockaddr*) &peer, peerlen) < 0 ) {
            error(1, errno, "SEND_TO FUNCTION MISTAKE");
        }
    }
}
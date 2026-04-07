#include "skel_defines.h"

ERROR_FORWARD_DECL
UDP_SERVER_FORWARD
SET_ADDRESS_FORWARD_DECL

static void server(SOCKET s, SIN* local);


int main( int argc, char** argv) {

    struct sockaddr_in local;
    char* hostName = DEFAULT_HOST;
    char* portNumber = DEFAULT_PORT;

    SOCKET sock;

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

    sock = udp_server(hostName, portNumber, &local);
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
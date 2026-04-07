#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL
//TCP_CLIENT_FORWARD
CLIENT_FUNC_FORWARD_DECL

int main( int argc, char** argv ) {

    SIN peer;
    SOCKET sock;

    char* host = DEFAULT_HOST;
    char* portNumber = DEFAULT_PORT;
    char* protocol =  {"udp"};

    switch(argc) {
    case 1:
        puts("NO HOST ADDRESS OR PORT WAS PROVIDED. EXIT.\n");
        EXIT(1);
    case 2:
        host = "127.0.0.1";
        portNumber = argv[1];
        break;
    case 3:
        host = argv[1];
        portNumber = argv[2];
        break;
    default:
        break;
    };

    INIT();

    set_address(host, portNumber, &peer, protocol);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if ( !IS_VALID_SOCKET(sock) ) {
        error(1, errno, "SOCKET FUNCTION MISTAKE");
    }

    client(sock, &peer);

    EXIT(0);
}

static void client(SOCKET s, SIN* peer) {
    int rc = 0;
    int peerlen;
    char buf[120];

    peerlen = sizeof(*peer);

    if ( sendto(s, "", 1, 0, (struct sockaddr*)peer, peerlen) < 0 ) {
        error(1, errno, "SENT_TO FUNCTION MISTAKE");
    }
    rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)peer, &peerlen);

    if (rc >= 0) {
        write( 1, buf, rc );
    } else {
        error(1, errno, "RECVFROM FUNCTION MISTAKE");
    }
}

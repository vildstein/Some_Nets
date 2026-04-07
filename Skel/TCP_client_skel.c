#include "skel_defines.h"

ERROR_FORWARD_DECL
//SET_ADDRESS_FORWARD_DECL
TCP_CLIENT_FORWARD
CLIENT_FUNC_FORWARD_DECL

int main( int argc, char** argv ) {

    SIN peer;
    SOCKET s;

    char* host = DEFAULT_HOST;
    char* port = DEFAULT_PORT;
    char* protocol = DEFAULT_NETWORK_PROTOCOL;

    const int on = 1;

    switch(argc) {
    case 1:
    case 2:
        break;
    case 3:
        host = argv[1];
        port = argv[2];
        break;
    default: break;
    };

    INIT();

    s = tcp_client(host, port);

    client(s, &peer);

    EXIT(0);
}

static void client(SOCKET s, SIN* peer) {
    int rc = 0;
    char buf[120];

    for ( ; ; ) {
        rc = recv(s, buf, sizeof(buf), 0);
        if (rc <= 0) {
            break;
        }
        write(1, buf, rc);
    }
}

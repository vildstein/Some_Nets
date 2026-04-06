#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL
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

    set_address( host, port, &peer, protocol );

    s = socket(AF_INET, SOCK_STREAM, 0 );

    if (!IS_VALID_SOCKET(s)) {
        error(1, errno, "SOCK FUNC FAILED");
    }

    if (connect( s, STRUCT_SOCKADDR_CAST&peer, sizeof(peer))) {
        error(1, errno, "CONNECT FUNC FAILED");
    }

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

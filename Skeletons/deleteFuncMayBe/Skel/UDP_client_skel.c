#include "skel_defines.h"

ERROR_FORWARD_DECL
UDP_CLIENT_FORWARD
CLIENT_FUNC_FORWARD_DECL
PARSE_ARGS_FORWARD

int main( int argc, char** argv ) {

	SIN peer;
	SOCKET sock;

	INIT_PORT_AND_HOST
	parseClArgs(argc, argv, host, portNumber);

	INIT();

	sock = udp_client(host, portNumber, &peer);

	client(sock, &peer);

	EXIT(0);
}

static void client(SOCKET s, SIN* peer) {
	int rc = 0;
	int peerlen;
	char buf[120];

	peerlen = sizeof(*peer);

	if ( sendto(s, "", 1, 0, SA peer, peerlen) < 0 ) {
		error(1, errno, "SENT_TO FUNCTION MISTAKE");
	}

	rc = recvfrom(s, buf, sizeof(buf), 0, SA peer, &peerlen);

	if (rc >= 0) {
		write( 1, buf, rc );
	} else {
		error(1, errno, "RECVFROM FUNCTION MISTAKE");
	}
}

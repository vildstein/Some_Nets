#include "skel_defines.h"

ERROR_FORWARD_DECL
TCP_CLIENT_FORWARD
CLIENT_FUNC_FORWARD_DECL
PARSE_ARGS_FORWARD

int main( int argc, char** argv ) {

	SIN peer;
	SOCKET s;

	INIT_PORT_AND_HOST
	parseClArgs(argc, argv, host, portNumber);

	INIT();

	s = tcp_client(host, portNumber);

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

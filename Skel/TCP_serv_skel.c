#include "skel_defines.h"

ERROR_FORWARD_DECL
SERVER_FUNC_FORWARD_DECL
TCP_SERVER_FORWARD
PARSE_ARGS_FORWARD

int main( int argc, char** argv) {

	struct sockaddr_in local;
	struct sockaddr_in peer;

	SOCKET answeringSocket;
	SOCKET listeningSocket;

	const int on = 1;

	INIT();

	INIT_PORT_AND_HOST
	parseClArgs(argc, argv, host, portNumber);

	listeningSocket = tcp_server(host, portNumber);
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
	const char* answer =  {"TCP Serv Skeleton Answer\n\n\n"};
	send(s, answer, strlen(answer), 0);
}

static void ans(SOCKET s, const char* ans) {
	const char* answer =  ans;
	send(s, answer, strlen(answer), 0);
}

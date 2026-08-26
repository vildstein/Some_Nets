#ifndef TCP_FUNCTIONS_H
#define TCP_FUNCTIONS_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL

#define NO_ADDITIONAL_PROTOCOL_REQUIRED 0

SOCKET tcp_client(char* hostName, char* portName) {

	struct sockaddr_in peer;
	SOCKET sock;

	set_address(hostName, portName, &peer, TCP_NETWORK_PROTOCOL);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if ( !IS_VALID_SOCKET(sock) ) {
		error( 1, errno, "SOCKET FUNC MISTAKE");
	}
	if ( connect(sock, (struct sockaddr*) &peer, sizeof(peer)) ) {
		error( 1, errno, "CONNECT FUNC MISTAKE");
	}
	return sock;
}

SOCKET tcp_server(char* hostName, char* portName, struct sockaddr_in* local) {

	SOCKET sockDecriptor;

	set_address(hostName, portName, local, TCP_NETWORK_PROTOCOL);
	sockDecriptor = socket(AF_INET, SOCK_STREAM, NO_ADDITIONAL_PROTOCOL_REQUIRED);

	if (!IS_VALID_SOCKET( sockDecriptor )) {
		error( 1, errno, "SOCKET FUNC MISTAKE");
	}

	const int TURN_SOCK_OPTS_ON = 1;
	if ( setsockopt(sockDecriptor, SOL_SOCKET, SO_REUSEADDR, &TURN_SOCK_OPTS_ON, sizeof(TURN_SOCK_OPTS_ON)) ) {
		error( 1, errno, "SET_SOCKET_OTP FUNC MISTAKE");
	}

	int localSize = sizeof(*local);
	if ( bind( sockDecriptor, SA local, sizeof(*local)) ) {
		error( 1, errno, "BIND FUNC MISTAKE");
	}

	if ( listen( sockDecriptor, NLISTEN) ) {
		error( 1, errno, "LISTEN FUNC MISTAKE");
	}

	return sockDecriptor;
}

#endif //TCP_FUNCTIONS_H

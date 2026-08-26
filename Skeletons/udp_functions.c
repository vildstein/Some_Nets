#ifndef UDP_FUNCTIONS_H
#define UDP_FUNCTIONS_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL

// int recvfrom(SOCKET sd, void* buf, size_t len, int flags, struct sockaddr* from, int* fromlen);
// int sendto (SOCKET sd, const void* buf, size_t len, int flags, struct sockaddr* to, int tolen);

SOCKET udp_client(char* hostName, char* portName, struct sockaddr_in* sp) {

	SOCKET sock;

	set_address(hostName, portName, sp, UDP_NETWORK_PROTOCOL);
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if ( !IS_VALID_SOCKET(sock) ) {
		error( 1, errno, "SOCKET FUNC MISTAKE" );
	}

	return sock;
}

SOCKET udp_server(char* hostName, char* portName, struct sockaddr_in* local) {

	SOCKET sock;

	/*NULL*/
	set_address(hostName, portName, local, UDP_NETWORK_PROTOCOL);

	sock = socket( AF_INET, SOCK_DGRAM, 0 );

	if (!IS_VALID_SOCKET( sock )) {
		error( 1, errno, "SOCKET FUNC MISTAKE");
	}

	if ( bind ( sock, SA local, sizeof(*local) ) ) {
		error( 1, errno, "BIND FUNC MISTAKE");
	}

	return sock;
}

#endif //UDP_FUNCTIONS_H

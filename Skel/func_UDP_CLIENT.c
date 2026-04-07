#ifndef UDP_CLIENT_FUNC_H
#define UDP_CLIENT_FUNC_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL

SOCKET udp_client(char* hostName, char* portName, struct sockaddr_in* sp) {

	SOCKET sock;
	
	set_address(hostName, portName, sp, "udp");
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if ( !IS_VALID_SOCKET(sock) ) {
		error( 1, errno, "SOCKET FUNC MISTAKE");
	}
	
	return sock;
}
#endif //UDP_CLIENT_FUNC_H

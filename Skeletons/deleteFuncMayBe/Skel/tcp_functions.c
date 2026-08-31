#ifndef TCP_FUNCTIONS_H
#define TCP_FUNCTIONS_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL

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

SOCKET tcp_server (char* hostName, char* portName) {

	struct sockaddr_in local;
	SOCKET socket;

	const int on = 1;

	set_address( hostName, portName, &local, TCP_NETWORK_PROTOCOL );

	socket = ( AF_INET, SOCK_STREAM, 0 );

	if (!IS_VALID_SOCKET( socket )) {
		error( 1, errno, "SOCKET FUNC MISTAKE");
	}

	if ( setsockopt( socket, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof(on)) ) {
		error( 1, errno, "SET_SOCKET_OTP FUNC MISTAKE");
	}

	if ( bind ( socket, SA &local, sizeof(local)) ) {
		error( 1, errno, "BIND FUNC MISTAKE");
	}

	if ( listen( socket, NLISTEN) ) {
		error( 1, errno, "LISTEN FUNC MISTAKE");
	}

	return socket;
}

// unsigned long int ntohl, unsigned short int ntol ntohs преобразует двоичные данные из сетевого порядка следования байтов в серверный.
// https://www.opennet.ru/man.shtml?topic=ntohl&category=3&russian=0

int readn(SOCKET socDescriptor, char* bufferToRead, size_t messageLenght) {

	int count = 0;
	int recived = 0;

	count = messageLenght;

	while (count > 0) {
		recived = recv(socDescriptor, bufferToRead,  count, 0);

		if (recived < 0) {
			if (errno == EINTR) {
				continue;
			}
			return -1;
		}

		if (recived == 0) {
			return 	messageLenght - count;
		}

		bufferToRead += recived;
		count -= recived;

	}

	return messageLenght;
}

// Для чтения сообщения переменной длинны
int readvrec(SOCKET socDescriptor, char* bufferToRead, size_t messageLenght) {

	u_int32_t recLenght = 0;
	int recived = 0;

	// read record lenght
	recived = readn(socDescriptor, bufferToRead, messageLenght);

	if (recived != sizeof(u_int32_t)) {
		return recived < 0 ? -1 : 0;
	}

	recLenght = ntohl(recLenght);
	if (recLenght > messageLenght) {

		// Not enought free space in buffer
		// return errno*/
		while (recLenght > 0) {
			recived = readn(socDescriptor, bufferToRead, messageLenght);
			if (recived != messageLenght) {
				return recived < 0 ? -1 : 0;
			}
			recLenght -= messageLenght;
			if (recLenght < messageLenght) {
				messageLenght = recLenght;
			}
		}
		// set_errno(EMSGSIZE);
		return -1;
	}

	// read the messgae
	recived = readn(socDescriptor, bufferToRead, messageLenght);
	if (recived != recLenght) {
		return recived < 0 ? -1 : 0;
	}

	return recLenght;
}


#endif //TCP_FUNCTIONS_H

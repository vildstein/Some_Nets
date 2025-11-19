#include "skel_defines.h"

ERROR_FORWARD_DECL
UDP_SERVER_FORWARD
SET_ADDRESS_FORWARD_DECL
PARSE_ARGS_FORWARD

static void echo_message(SOCKET s);


int main( int argc, char** argv) {

	struct sockaddr_in local;

	//INIT_PORT_AND_HOST
	//parseClArgs(argc, argv, host, portNumber);

	char* portNumber = "9000";

	if (argc > 1) {
		portNumber = argv[1];
	}

	printf("port defined as %s\n", portNumber);

	SOCKET sock;

	INIT();

	sock = udp_server(NULL, portNumber, &local);

	echo_message(sock);

	EXIT(0);
}

// int recvfrom(SOCKET sd, void* buf, size_t len, int flags, struct sockaddr* from, int* fromlen);
// int sendto (SOCKET sd, const void* buf, size_t len, int flags, struct sockaddr* to, int tolen);

static void echo_message(SOCKET s) {

	struct sockaddr_in from;
	socklen_t peerlen;

	const size_t biff_size = 512;

	char buffer[biff_size];

	char message[] = "hello world FUCK OFF Maza Faka\n";

	const int NO_FLAGS = 0;

	fd_set fd_AllSd;
	fd_set fd_readedSd;

	FD_ZERO(&fd_AllSd);
	FD_SET(s, &fd_AllSd);

	struct timeval tv_str;
	tv_str.tv_sec = 10;
	tv_str.tv_usec = 0;

	int sd_count = 0;
	int bytesReciced = 0;

	for (;;) {

		peerlen = sizeof(from);

		fd_readedSd = fd_AllSd;

		sd_count = select( (s + 1),  &fd_readedSd, NULL, NULL, &tv_str );

		if (sd_count < 0) {
			error(1, errno, "SELECT FUNCTION MISTAKE");
		}

		if (SELECT_FUNC_NO_TIMEOUT(sd_count)) {

			if ( FD_ISSET(s, &fd_readedSd) ) {

				bytesReciced = recvfrom(s, buffer, sizeof(buffer), NO_FLAGS, SA &from, &peerlen);

				if ( bytesReciced < 0 ) {
					error(1, errno, "RECVFROM FUNCTION MISTAKE");
				} else {
					//ston from.sin_addr;
					//in_port_t portNum = from.sin_port;
					//int portStr = ntohs(portNum);
					//struct in_addr sin_addr_struct = from.sin_addr;
					//int port = inet_pton(portNum);

					char* host = inet_ntoa(from.sin_addr);
					//int port = ntohs(from.sin_port);
					if (host != NULL) {
						printf("recieved %d bytes from host %s\n", bytesReciced, host);
					}

					int sended = sendto(s, buffer, sizeof(buffer), NO_FLAGS, SA &from, peerlen);

					if (sended < 0) {
						error(1, errno, "SEND_TO FUNCTION MISTAKE");
					} else {
						printf("sended %d bytes to host %s\n", bytesReciced, host);
					}
				}

				break;

			} else {
				error(1, errno, "FD_SET IS NOT ABLE WORK WITH PROVIDED SOCKET.");
			}

		} else if (SELECT_FUNC_TIMEOUT(sd_count)) {
			printf("SELECT FUNCTION TIME OUT. NO CONNECTION.\n");
			break;
			//error(1, errno, "SELECT FUNCTION TIME OUT. NO CONNECTION.");
		}
	}
}

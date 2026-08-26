#ifndef PARSE_CL_ARGS_FUNCTIONS_H
#define PARSE_CL_ARGS_FUNCTIONS_H

#include "skel_defines.h"

ERROR_FORWARD_DECL

void parseClArgs(int argc, char** argv, char* hostNumber, char* portNumber) {

	switch(argc) {
	case 1: {
			puts("NO HOST ADDRESS OR PORT WAS PROVIDED. DEFINED DEFAULT VALUES.\n");
			strcpy(hostNumber, LOCAL_HOST);
			strcpy(portNumber, DEFAULT_PORT);
		}
		break;
	case 2: {
			// ДОДЕЛАТЬ c возможностью отличать адрес В4 от порта!!!
			strcpy(hostNumber, LOCAL_HOST);
			strcpy(portNumber, argv[1]);
		}
		break;
	case 3: {

			int addrLen = strlen(argv[1]);
			int portLen = strlen(argv[2]);

			if (addrLen <= V4_ADDR_SIZE) {
				strncpy(hostNumber, argv[1], addrLen);
			} else {
				error( 1, errno, "INVALID IP ADDRES" );
			}

			if (portLen <= V4_ADDR_SIZE) {
				strncpy(portNumber, argv[2], portLen);
			} else {
				error( 1, errno, "INVALID POR ADDRES" );
			}
		}
		break;
	default:
		break;
	};

	printf("host defined as %s\n", hostNumber);
	printf("port defined as %s\n", portNumber);
}

#endif //UDP_FUNCTIONS_H

#ifndef TCP_CLIENT_FUNC_H
#define TCP_CLIENT_FUNC_H

#include "skel_defines.h"

ERROR_FORWARD_DECL
SET_ADDRESS_FORWARD_DECL

SOCKET tcp_client(char* hostName, char* portName) {

  struct sockaddr_in peer;
  SOCKET sock;

  set_address(hostName, portName, &peer, "TCP");

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if ( !IS_VALID_SOCKET(sock) ) {
    error( 1, errno, "SOCKET FUNC MISTAKE");
  }

  if ( connect(sock, (struct sockaddr*) &peer, sizeof(peer)) ) {
    error( 1, errno, "CONNECT FUNC MISTAKE");
  }

  return sock;
}


#endif //TCP_CLIENT_FUNC_H

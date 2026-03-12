#ifndef INCLUDE_H
#define INCLUDE_H

// Move to include
#include <sys/types.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //sockaddr_in, htons
#include <string.h>
#include <stdio.h> //puts()
#include <stdarg.h> //va_list

#define BZERO_MACRO(ptr, n) memset(ptr, 0, sizeof(n) )
#define SA struct sockaddr
#define MAXLINE 4096

#define LISTENQ 1024


#endif /*INCLUDE_H*/
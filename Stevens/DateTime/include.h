#ifndef INCLUDE_H
#define INCLUDE_H

// Move to include
#include <syslog.h> // LOG_ERR
#include <sys/types.h>
#include <sys/socket.h> // socket
#include <sys/errno.h>
#include <netinet/in.h> // sockaddr_in, htons
#include <string.h>
#include <stdio.h> // puts()
#include <stdarg.h> // va_list
#include <stdlib.h>
#include <errno.h>


#define BZERO_MACRO(ptr, n) memset(ptr, 0, sizeof(n) )
#define SA struct sockaddr
#define MAXLINE 4096

#define CLIENTS_LISTEN_QUANTITY 1024 //


#endif /*INCLUDE_H*/
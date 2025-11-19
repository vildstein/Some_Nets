#include "include.h"

#include <time.h>
#include <unistd.h>


// PRESENTATION_TO_NUMERIC
// int inet_pton(int af, const char *src, void *dst); Преобразует адрес в двоичную форму

// unsigned long int inet_addr(const char* ip_address); УСТАРЕВШАЯ Преобразует IP адрес из точечной нотации в двоичную форму
// с сетевым порядком следования байтов. Лучше использовать inet_aton()

// int inet_aton(const char* ip_addr, struct in_addr* addr); Преобразует IP адрес из точечной нотации в двоичную форму с 
//сетевым порядком следования байтов.

// HOST_TO_NETWORK_SHORT
// uint16_t htons(uint16_t hostshort); //Преобразует двоичные данные из сетевого порядка следования байтов в серверный

// HOST_TO_NETWORK_LONG
// uint32_t htonl(uint32_t hostshort); //Преобразует двоичные данные из сетевого порядка следования байтов в серверный

// int socket(int domain, int type, int protocol);
// int connect(int socketDiscriptor, struct sockaddr* addr, int addr_len);

// int read(int fd, char* buffer, size_t buf_len); Читает указанное число байтов из файла с дескриптором fd и помещает результат
// в буфер. Возвращает число прочитанных байтов.


static void err_doit(int errnoflag, int level, const char* fmt, va_list ap)
{
	int daemon_proc = 0;
	int errno_save, n;
	char buf[MAXLINE + 1];
	errno_save = errno; /* value caller might want printed */

#ifdef  HAVE_VSNPRINTF
	vsnprintf(buf, MAXLINE, fmt, ap);       /* safe */
#else
	vsprintf(buf, fmt, ap);                                 /* not safe */
#endif
	n = strlen(buf);
	if (errnoflag)
		snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
		strcat(buf, "\n");

	if (daemon_proc) {
		syslog(level, buf);
	} else {
		fflush(stdout);         /* in case stdout and stderr are the same */
		fputs(buf, stderr);
		fflush(stderr);
	}
	return;
}


void err_sys(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}


int SocketFuncWrap(int family, int type, int protocol)
{
	int n;
	if ( (n = socket(family, type, protocol)) < 0) {
		err_sys("socket error");
	}
	
	return(n);
}

void BindFuncWrap(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		err_sys("bind error");
}




//void BindFuncWrap(int fd, const struct sockaddr *sa, socklen_t salen)
//{
//    if (bind(fd, sa, salen) < 0)
//        err_sys("bind error");
//}

void ListenFuncWrap(int fd, int backlog)
{
	char *ptr;
	/*4can override 2nd argument with environment variable */
    //if ( (ptr = getenv("CLIENTS_LISTEN_QUANTITY")) != NULL) {
	//	backlog = atoi(ptr);
	//}
	if (listen(fd, backlog) < 0) {
		err_sys("listen error");
	}			
}

//ACCEPT
//int AcceptFuncWraps(int fd, struct sockaddr *sa, socklen_t *salenptr)
//{
//	int n;
//again:
//	if ( (n = accept(fd, sa, salenptr)) < 0) {
//#ifdef  EPROTO
//	if (errno == EPROTO || errno == ECONNABORTED) {
//#else
//	if (errno == ECONNABORTED) {
//#endif
//	goto again;
//	} else {
//		err_sys("accept error");
//	}
//	return(n);
//}

int AcceptFuncWrap(int fd, struct sockaddr *sa, socklen_t *salenptr) {
	int n;
	if ( (n = accept(fd, sa, salenptr)) < 0) {
		err_sys("accept error");
	}
	return(n);
}

//WRITE
void WriteFuncWrap(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes) {
		err_sys("write error");
	}                
}


void CloseFuncWrap(int fd) {
	if (close(fd) == -1) {
		err_sys("close error");
	}                
}


int main(int argc, char** argv) {

	const int portNumber = 13;
	int listenSockDescr = 0;
	int nBytesRead = 0;
	char buff[MAXLINE + 1];
	time_t ticks;

	struct sockaddr_in servaddr;

	const char* localAdress = "127.0.0.1";
	//argc == 1 ? : "127.0.0.1" ;

	if (argc == 1) {
		puts("usage /*ОПРЕДЕЛИТЬ имя исполняемого файла в CMAKE*/: <IPaddress>");
		//puts("IP address defined as 127.0.0.1");
		//err_quit("usage /*ОПРЕДЕЛИТЬ имя исполняемого файла в CMAKE*/: <IPaddress>");
		return 1;
	} else if (argc > 2) {
		puts("usage /*ОПРЕДЕЛИТЬ имя исполняемого файла в CMAKE*/: <IPaddress>");
		//puts("Please, enter a IP address");
		return 1;
	} 

	//listenSockDescr = socket(AF_INET, SOCK_STREAM, 0);
	//if (listenSockDescr < 0) {
		//err_sys("socket func ERROR");
	//	puts("Please, enter a IP address");
	//	return 1;
	//}

	listenSockDescr = SocketFuncWrap(AF_INET, SOCK_STREAM, 0);

	BZERO_MACRO(&servaddr, servaddr );

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	servaddr.sin_port = htons(portNumber);

	BindFuncWrap(listenSockDescr, (SA*) &servaddr, sizeof(servaddr));
	
	ListenFuncWrap(listenSockDescr, CLIENTS_LISTEN_QUANTITY);

	int connectedDescriptor = 0;

	
	//"%.24s\er\en"
	for (;;) {
		connectedDescriptor = AcceptFuncWrap(listenSockDescr, (SA*) NULL, NULL);

		ticks = time( NULL);
		snprintf(buff, sizeof(buff), "%.24s\er\en", ctime(&ticks));
		WriteFuncWrap(connectedDescriptor, buff, strlen(buff));
		CloseFuncWrap(connectedDescriptor);
	}

	return 0;
}

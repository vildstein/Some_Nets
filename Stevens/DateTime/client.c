#include "include.h"


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


static void err_doit(int, int, const char* , va_list) {

}

/*
void err_sys(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	
	exit(1);
}
*/


int main(int argc, char** argv) {

	const int portNumber = 13;
	int sockDescr = 0;
	int nBytesRead = 0;
	char recieveLine[MAXLINE + 1];
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

	sockDescr = socket(AF_INET, SOCK_STREAM, 0);
	if (sockDescr < 0) {
		//err_sys("socket func ERROR");
		puts("Please, enter a IP address");
		return 1;
	}

	//bzero(&servaddr, sizeof(servaddr) );

	BZERO_MACRO(&servaddr, servaddr );

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portNumber);

	//char* ip = (argc == 1) ? localAdress : argv[1];

	int adressCast = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	if (adressCast <= 0) {
		//err_quit("inet_pton func error for %s", argv[1]);
		puts("Please, enter a IP address");
		return 1;
	}

	int conectResult = connect(sockDescr, (SA*) &servaddr,      sizeof(servaddr));
	if (conectResult < 0) {
		//err_sys("connect function ERROR");
		puts("Please, enter a IP address");
		return 1;
	}

	while ((nBytesRead = read(sockDescr, recieveLine, MAXLINE)) > 0) {
		recieveLine[nBytesRead] = 0;
		if (fputs(recieveLine, stdout) == EOF ) {
			puts("fputs function ERROR. Return.");
			return 1;
		}
	}

	if (nBytesRead < 0) {
		puts("Read ERROR. Return.");
		return 1;
	}


	return 0;
}

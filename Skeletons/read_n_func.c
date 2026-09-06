#ifndef READ_N_FUNC_H
#define READ_N_FUNC_H

#include "skel_defines.h"
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <errno.h>

// unsigned long int ntohl, unsigned short int ntol ntohs преобразует двоичные данные из сетевого порядка следования байтов в серверный.
// https://www.opennet.ru/man.shtml?topic=ntohl&category=3&russian=0

int readn(SOCKET socDescriptor, char* bufferToRead, size_t messageLenght) {

	int count = 0;
	int recived = 0;

	count = messageLenght;

	while (count > 0) {
		recived = recv(socDescriptor, bufferToRead, count, MSG_NOSIGNAL);
		printf("recieved %d bytes\n", recived);

		if (recived < 0) {
			if (errno == EINTR) {
				continue;
			}
			return -1;
		}

		if (recived == 0) {
			return (messageLenght - count);
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
	recived = readn(socDescriptor, (char*) &recLenght, sizeof(recLenght));

	if ( recived != sizeof(u_int32_t) ) {
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
		errno = EMSGSIZE;
		return -1;
	}

	// read the messgae
	recived = readn(socDescriptor, bufferToRead, messageLenght);
	if (recived != recLenght) {
		return recived < 0 ? -1 : 0;
	}

	return recLenght;
}

int readline(SOCKET socDescriptor, char* bufferToRead, size_t buffLen) {

    char* buffInitial = bufferToRead;
    static char* bp;
    static int count = 0;
    static char additionalBuff[1500];

    char ch;

    const int NO_RECIVE_FLAGS = 0;

    while(--buffLen > 0) {
        if (--count <= 0) {
            count = recv(socDescriptor, additionalBuff, sizeof(additionalBuff), NO_RECIVE_FLAGS);
            if (count < 0) {
                if (errno == EINTR) {
                    buffLen++;
                    continue;
                }
                return -1;
            }
            if (count == 0) {
                return 0;
            }

        }

        bufferToRead = additionalBuff; //???
        *bufferToRead++ = ch;
        if (ch == '\n') {
            *bufferToRead++ = '\n';
            return bufferToRead - buffInitial;
        }
    }
    errno = EMSGSIZE;
    return -1;
}


#endif //ERROR_FUNC_H

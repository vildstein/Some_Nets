#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(void) {

    WSADATA data;

    if (WSAStartup(MAKEWORD(2, 2), &data)) {
        printf("Failed to initialize.\n");
        return -1;
    }

    WSACleanup();
    printf("Ok\n");


    return 0;
}

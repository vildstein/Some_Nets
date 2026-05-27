#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

int main() {

    WSADATA d;

    if (WSAStartup(MAKEWORD(2, 2), &d) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return -1;
    }

    DWORD asize = 20000;
    PIP_ADAPTER_ADDRESSES adapters;

    do {
        adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);

        if (adapters == NULL) {
            printf("could not allocate: %ld bytes for adapters.\n", asize);
            WSACleanup();
            return -1;
        }

        int r = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters, &asize);

        if (r == ERROR_BUFFER_OVERFLOW) {
            printf("GetAdaptersAddresses wants : %ld bytes. \n", asize);
            free(adapters);
        } else if (r == ERROR_SUCCESS) {
            break;
        } else {
            printf("GetAdaptersAddresses failed with error: %d\n", r);
            free(adapters);
            WSACleanup();
            return -1;

        }
    } while ( !adapters );

    PIP_ADAPTER_ADDRESSES adapter = adapters;

    while (adapter != NULL) {
        printf("\nAdapter Name: %S\n", adapter->FriendlyName);

        PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
        printf("\t%s", address->Address.lpSockaddr->sa_family == AF_INET ? "IPv4" : "IPv6");

        char ap[100];

        getnameinfo(address->Address.lpSockaddr, address->Address.iSockaddrLength,
            ap,
            sizeof(ap),
            0,
            0,
            NI_NUMERICHOST);
        printf("\t %s \n", ap);
        address = address->Next;
        adapter = adapter->Next;
    }
    free(adapters);
    WSACleanup();
    puts("cleaned up");



    return 0;
}

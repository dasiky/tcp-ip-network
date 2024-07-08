#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("useage: %s <addr>\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    struct hostent* phostent = gethostbyaddr((char*)&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
    printf("h_name: %s\n", phostent->h_name);

    for (int i = 0; phostent->h_aliases[i]; i++)
        printf("h_aliases: %s\n", phostent->h_aliases[i]);

    printf("address type: %s\n", (phostent->h_addrtype == AF_INET ? "ipv4": "ipv6"));

    for (int i = 0; phostent->h_addr_list[i]; i++)
        printf("h_addr: %s\n", inet_ntoa(*(struct in_addr*)phostent->h_addr_list[i]));
}
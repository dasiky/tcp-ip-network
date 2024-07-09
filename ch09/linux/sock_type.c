#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char** argv) {
    int tcp_sock, udp_sock;

    tcp_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    udp_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    printf("SOCKE_STREAM: %d\n", SOCK_STREAM);
    printf("SOCKE_DGRAM: %d\n", SOCK_DGRAM);

    int sock_type, type_len = sizeof(sock_type);
    getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, &sock_type, &type_len);
    printf("tcp sock type: %d\n", sock_type);
    type_len = sizeof(sock_type);
    getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, &sock_type, &type_len);
    printf("udp sock type: %d\n", sock_type);

    return 0;
}
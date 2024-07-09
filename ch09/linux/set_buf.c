#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char** argv) {
    int sock;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    int set_sendbuf = 1024 * 3, set_recvbuf = 1024 * 3;
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &set_sendbuf, sizeof(set_sendbuf));
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &set_recvbuf, sizeof(set_recvbuf));

    int get_sendbuf, get_recvbuf, sz;
    sz = 4;
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &get_sendbuf, &sz);
    sz = 4;
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &get_recvbuf, &sz);

    printf("send buffer: %d\n", get_sendbuf);
    printf("receive buffer: %d\n", get_recvbuf);
}
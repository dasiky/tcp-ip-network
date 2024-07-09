#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char** argv) {
    int sock;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    int sendbuf, recvbuf, sz;
    sz = 4;
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, &sz);
    sz = 4;
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, &sz);

    printf("send buffer: %d\n", sendbuf);
    printf("receive buffer: %d\n", recvbuf);
}
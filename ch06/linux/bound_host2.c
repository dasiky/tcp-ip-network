#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("useage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    struct sockaddr_in serv_addr, from_addr;
    socklen_t addr_sz;

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1)
        error_handling("socket() error");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    char msg1[] = "Hi!";
    char msg2[] = "I'm another UDP host!";
    char msg3[] = "Nice to meet you";
    sendto(sock, msg1, strlen(msg1), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, msg2, strlen(msg2), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, msg3, strlen(msg3), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    close(sock);
    return 0;
}
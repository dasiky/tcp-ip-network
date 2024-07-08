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
    
    char message[BUF_SIZE];
    while(1) {
        fputs("Input: ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if (strcmp("q\n", message) == 0)
            break;

        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        addr_sz = sizeof(from_addr);
        int str_len = recvfrom(sock, message, BUF_SIZE - 1, 0, (struct sockaddr*)&from_addr, &addr_sz);
        message[str_len] = 0;

        printf("receive from server: %s", message);
    }

    close(sock);
    return 0;
}
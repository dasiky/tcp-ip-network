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

#define BUF_SZ 1024

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("useage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
        error_handling("socket() error");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");
    else
        puts("connected.........");
    
    char message[BUF_SZ];
    while(1) {
        fputs("Input: ", stdout);
        fgets(message, BUF_SZ, stdin);

        if (strcmp("q\n", message) == 0)
            break;

        write(sock, message, strlen(message));
        int str_len = read(sock, message, BUF_SZ - 1);
        message[str_len] = 0;
        printf("receive from server: %s", message);
    }
    close(sock);
    return 0;
}
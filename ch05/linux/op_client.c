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
    int op_cnt, operand;
    char operator;

    fputs("Operand count: ", stdout);
    scanf("%d", &op_cnt);
    write(sock, &op_cnt, 4);

    for (int i = 0; i < op_cnt; i++) {
        printf("Operand %d: ", i + 1);
        scanf("%d", &operand);
        write(sock, &operand, 4);
    }

    printf("Operator: ");
    scanf("\n%c", &operator);
    write(sock, &operator, 1);

    int res;
    read(sock, &res, 4);
    printf("Operation result: %d\n", res);

    close(sock);
    return 0;
}
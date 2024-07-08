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

int calculate(char operator, int op_cnt, int* oprands) {
    int res = 0;

    for (int i = 0; i < op_cnt; i++) {
        if (operator == '+')
            res += oprands[i];
        else
            res -= oprands[i];
    }

    return res;
}

int main(int argc, char** argv) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz = sizeof(clnt_addr);


    if (argc != 2) {
        printf("useage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv_sock == -1)
        error_handling("socket() error");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while(1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);
        if (clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connect %s:%d\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

        int str_len, str_count = 0;
        int op_cnt;
        // read operand count
        read(clnt_sock, &op_cnt, 4);

        // read operands and operator
        while (str_count < op_cnt * 4 + 1) {
            if ((str_len = read(clnt_sock, &message[str_count], BUF_SIZE - str_count)) <= 0)
                error_handling("read() error");
            printf("%d\n", str_len);
            str_count += str_len;
        }

        int res = calculate(message[op_cnt * 4], op_cnt, (int*)message);
        write(clnt_sock, &res, 4);

        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}
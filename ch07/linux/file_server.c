#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

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

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 1);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);

    FILE* fp = fopen("file_server.c", "rb");
    char buf[BUF_SIZE];
    int read_cnt;
    while(1) {
        read_cnt = fread(buf, 1, BUF_SIZE, fp);
        write(clnt_sock, buf, read_cnt);
        if (read_cnt < BUF_SIZE)
            break;
    }
    shutdown(clnt_sock, SHUT_WR);
    read(clnt_sock, buf, BUF_SIZE);
    printf("receive from client: %s\n", buf);

    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
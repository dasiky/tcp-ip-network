#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("useage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    puts("connected.........");
    
    FILE* fp = fopen("receive.dat", "wb");

    char message[BUF_SIZE];
    int str_len;
    while((str_len = read(sock, message, BUF_SIZE - 1)) != 0) {
        message[str_len] = 0;
        printf("%s", message);
        fwrite(message, 1, str_len, fp);
    }
    write(sock, "Thank you", 10);

    fclose(fp);
    close(sock);
    return 0;
}
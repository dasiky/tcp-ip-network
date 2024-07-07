#include <stdio.h>
#include <winsock2.h>

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    error_handling("WSAStartup() error!");

    {
        char* addr = "127.212.124.78";
        unsigned long conv_addr = inet_addr(addr);
        if (conv_addr == INADDR_NONE)
            printf("error\n");
        else
            printf("network order: %#lx \n", conv_addr);
    }

    {
        struct sockaddr_in addr;
        char* strPtr;
        char strArr[20];

        addr.sin_addr.s_addr = htonl(0x1020304);
        strPtr = inet_ntoa(addr.sin_addr);
        strcpy(strArr, strPtr);
        printf("%s\n", strArr);
    }
    WSACleanup();
    return 0;
}

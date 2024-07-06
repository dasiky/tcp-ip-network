#include<iostream>
#include<winsock2.h>
using namespace std;

void ErrorHandling(const string& message) {
    cerr << message << endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    WSADATA WSAData;
    SOCKET hSock;
    SOCKADDR_IN servAddr;

    char message[30];
    int idx = 0, readLen, strLen = 0;
    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 初始化 socket 库
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
        ErrorHandling("WSAStartup() error!");

    // 创建 socket
    hSock = socket(PF_INET, SOCK_STREAM, 0);
    if (hSock == INVALID_SOCKET)
        ErrorHandling("socket() error!");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    // 连接
    if (connect(hSock, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("connect() error!");

    while(readLen = recv(hSock, &message[idx++], 1, 0)) {
        if (readLen == -1)
            ErrorHandling("recv() error!");
        strLen += readLen;
    }
    cout << "Message from server: " << message << endl;
    cout << "Function read call count: " << strLen << endl;

    closesocket(hSock);

    // 注销 socket 库
    WSACleanup();
}
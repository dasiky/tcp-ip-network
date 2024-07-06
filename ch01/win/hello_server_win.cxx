#include<iostream>
#include<winsock2.h>
using namespace std;

void ErrorHandling(const string& message) {
    cerr << message << endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    WSADATA WSAData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;
    int szClntAddr = sizeof(clntAddr);
    char message[] = "Hello Socket!";
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // 初始化 socket 库
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
        ErrorHandling("WSAStartup() error!");

    // 创建 socket
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if (hServSock == INVALID_SOCKET)
        ErrorHandling("socket() error!");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(atoi(INADDR_ANY));
    servAddr.sin_port = htons(atoi(argv[1]));

    // 绑定地址端口
    if (bind(hServSock, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind() error!");

    // 开始监听
    if (listen(hServSock, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error!");

    // 接受连接
    hClntSock = accept(hServSock, (sockaddr*)&clntAddr, &szClntAddr);
    if (hClntSock == INVALID_SOCKET)
        ErrorHandling("accept() error!");

    send(hClntSock, message, sizeof(message), 0);
    closesocket(hClntSock);
    closesocket(hServSock);

    // 注销 socket 库
    WSACleanup();
}
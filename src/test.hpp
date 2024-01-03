#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <winsock2.h>   // Socket API
//#pragma comment(lib, "ws2_32.lib")  // vs studio中添加响应的lib，clion中需要在CMakeList中添加

class SocketTest {
public:
    // 初始化Socket
    static int initializeSocket() {
        // 初始化Socket库
        WSADATA wsaData;    // 用于保存winsock库信息的结构体
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "[Err]Failed to initialize winsock." << std::endl;
            return -1;
        }

        // 创建socket
        // AF_INET：IPv4 地址族。
        // AF_INET6：IPv6 地址族。
        // 其他一些如 AF_UNIX、AF_LOCAL 等，用于本地通信。
        // SOCK_STREAM：面向连接的流套接字，通常用于 TCP。
        // SOCK_DGRAM：面向消息的数据报套接字，通常用于 UDP。
        // SOCK_RAW：原始套接字，提供对网络层的原始访问。
        unsigned long long serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "[Err]Error Creating socket:" << strerror(errno) << std::endl;
            return -1;
        }

        // 绑定Socket的地址和端口
        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.S_un.S_addr = inet_addr("192.168.2.127");
        serverAddress.sin_port = htons(11451);
        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "[Err]Error binding socket:" << strerror(errno) << std::endl;
            return -1;
        }

        // 设置Socket为监听
        // backlog为最大等待队列
        if (listen(serverSocket, 5) == -1) {
            std::cerr << "[Err]Error listening on socket:" << strerror(errno) << std::endl;
            return -1;
        }

        // 接收连接
        // sockaddr_in结构体用来表示IPv4
        struct sockaddr_in clientAddress;
        int clientLength = sizeof(clientAddress);
        unsigned long long int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLength);
        if (clientSocket == -1) {
            std::cerr << "[Err]Error accepting connection:" << strerror(errno) << std::endl;
            return -1;
        }

        // 获取消息
        char buffer[1024];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "Read message:" << buffer << std::endl;
        }

        // 关闭Socket，释放资源
        closesocket(serverSocket);
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }
private:
};

#endif // TEST_HPP
//
// Created by 86188 on 2023/12/26.
//

#include "SocketCore.h"
#include <cstring>

SocketCore* SocketCore::createSocketAndListen(char* ip, int port, char* socketName, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength, SocketTaskManager* socketTaskManager) {
    // 指针判空
    if (ip == nullptr || socketName == nullptr) {
        return nullptr;
    }

    SocketCore* ret_SocketCore = new SocketCore(ip, port, socketName, ipv, socketT, waitingLength, socketTaskManager);
    // 初始化失败，释放内存
    if (ret_SocketCore->m_socketIndex == INVALID_SOCKET) {
        delete ret_SocketCore;
        ret_SocketCore = nullptr;
        return nullptr;
    }

    // 绑定地址
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = ret_SocketCore->m_IPv;
    serverAddr.sin_addr.S_un.S_addr = inet_addr(ret_SocketCore->m_IP);
    serverAddr.sin_port = htons(ret_SocketCore->m_Port);
    if (bind(ret_SocketCore->m_socketIndex, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        delete ret_SocketCore;
        ret_SocketCore = nullptr;
        return nullptr;
    }

    // 开启监听
    if (listen(ret_SocketCore->m_socketIndex, ret_SocketCore->m_WaitingLength) == -1) {
        delete ret_SocketCore;
        ret_SocketCore = nullptr;
        return nullptr;
    }

    return ret_SocketCore;
}

SocketCore::SocketCore(char* ip, int port, char* socketName, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength, SocketTaskManager* socketTaskManager)
    : m_socketIndex(socket(ipv, socketT, 0)),
      m_IP(new char[strlen(ip) + 1]), // RAII
      m_Port(port),
      m_SocketName(new char[strlen(socketName) + 1]), // RAII
      m_IPv(ipv),
      m_SocketT(socketT),
      m_WaitingLength(waitingLength),
      m_stopSignal(false),
      m_pSocketTaskManager(socketTaskManager){
    std::strcpy(m_IP, ip);
    std::strcpy(m_SocketName, socketName);
}

SocketCore::~SocketCore(){
    closesocket(m_socketIndex);
    delete[] m_IP; // RAII
    m_IP = nullptr;
    delete[] m_SocketName; // RAII
    m_SocketName = nullptr;
}

const char* SocketCore::getName() const {
    return m_SocketName;
}

const char* SocketCore::getBindIP() const {
    return m_IP;
}

int SocketCore::getBindPort() const {
    return m_Port;
}

Socket_Util::IPVersion SocketCore::getIPv() const {
    return m_IPv;
}

Socket_Util::SocketType SocketCore::getSocketType() const {
    return m_SocketT;
}

void SocketCore::acceptAndTask() {
    struct sockaddr_in clientAddress;
    char* buffer = new char[1024];
    while (!m_stopSignal) {
        // 接收连接
        int clientLength = sizeof(clientAddress);
        unsigned long long int clientSocket = accept(m_socketIndex, (struct sockaddr*)&clientAddress, &clientLength);
        if (clientSocket == -1) { // 连接失败
            continue; // 准备接收下一次连接
        }

        // 获取消息
        int bytesRead = recv(clientSocket, buffer, 1024, 0);
        if (bytesRead <= 0) {
            continue;
        }
        buffer[bytesRead] = '\0';
        char* taskName;
        char* arg;
        for (int i = 0; buffer[i] != 0; ++i) {
            if (buffer[i] == ',') { // 碰到的第一个逗号
                taskName = Socket_Util::splitIndex(buffer, 0, i);
                arg = Socket_Util::splitIndex(buffer, i + 1, strlen(buffer) + 1);
                break;
            }
        }
        m_pSocketTaskManager->runSocketTask(taskName, arg);
    }
}
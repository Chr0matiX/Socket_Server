//
// Created by 86188 on 2023/12/26.
//

#ifndef SOCKET_SERVER_SOCKETCORE_H
#define SOCKET_SERVER_SOCKETCORE_H

#include <winsock2.h>
#include "Util.hpp"

class SocketCore {
private:
    // Socket
    unsigned long long int m_socketIndex;

    // Bind
    char* m_IP;
    int m_Port;

    // Display Name
    char* m_SocketName;

    // Internet Protocol Version enum
    enum Socket_Util::IPVersion m_IPv;

    // Socket Type enum
    enum Socket_Util::SocketType m_SocketT;

    // 等待队列的长度
    int m_WaitingLength;

    SocketCore(char* ip, int port, char* socketName, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength);
    ~SocketCore();

public:
    // 创建一个Socket
    static SocketCore* createSocketAndListen(char* IP, int port, char* socketName, Socket_Util::IPVersion iPv, Socket_Util::SocketType socketT, int waitingLength);

    // 获取Socket名称
    [[nodiscard]] const char* getName() const;

    // 获取绑定的IP
    [[nodiscard]] const char* getBindIP() const;

    // 获取绑定的端口
    [[nodiscard]] int getBindPort() const;

    // 获取IPVersion
    [[nodiscard]] Socket_Util::IPVersion getIPv() const;

    // 获取SocketType
    [[nodiscard]] Socket_Util::SocketType getSocketType() const;
};


#endif //SOCKET_SERVER_SOCKETCORE_H

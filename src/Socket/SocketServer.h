//
// Created by 86188 on 2023/12/26.
//

#ifndef SOCKET_SERVER_SOCKETSERVER_H
#define SOCKET_SERVER_SOCKETSERVER_H

#include <vector>
#include <map>
#include "SocketCore.h"
#include "SocketTask/SocketTaskManager.h"

class SocketServer {
public:
    SocketServer();
    ~SocketServer();

    // 创建Socket对象并加入容器
    static bool addSocket(char* socketName, char* ip, int port, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength);

    // 从容器中移除Socket对象
    static bool removeSocket(char* socketName);

    // 注册任务管理对象
    SocketTaskManager* m_pSocketTaskManager;

private:
    // Socket容器
    static std::map<char*, SocketCore*> map_Sockets;
};


#endif //SOCKET_SERVER_SOCKETSERVER_H

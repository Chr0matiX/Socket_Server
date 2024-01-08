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
    // 创建Socket对象并加入容器
    static bool addSocket(char* socketName, char* ip, int port, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength, SocketTaskManager* pSocketTaskManager = m_pSocketTaskManager);

    // 从容器中移除Socket对象
    static bool removeSocket(char* socketName);

    // 任务管理对象
    static SocketTaskManager* m_pSocketTaskManager;

    // 初始化服务器
    static bool initializeSocketServer();

    // 释放服务器
    static bool deleteSocketServer();

private:
    // Socket容器
    static std::map<char*, SocketCore*> map_Sockets;
    // 单例
    SocketServer();
};


#endif //SOCKET_SERVER_SOCKETSERVER_H

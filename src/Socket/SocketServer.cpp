//
// Created by 86188 on 2023/12/26.
//

#include "SocketServer.h"

// 静态成员的初始化
std::map<char*, SocketCore*> SocketServer::map_Sockets;
SocketTaskManager* SocketServer::m_pSocketTaskManager = nullptr;

SocketServer::SocketServer() {
    m_pSocketTaskManager = new SocketTaskManager();
}

SocketServer::~SocketServer() {
    for (auto& it : map_Sockets) {
        delete it.second; // 先停止循环接收
        delete[] it.first;
        //it.first = nullptr; // 不被允许，it.first的类型为char* const，所以无法修改指针本身的值
    }
    map_Sockets.clear();
    delete m_pSocketTaskManager;
    m_pSocketTaskManager = nullptr;
}

bool SocketServer::addSocket(char* socketName, char* ip, int port, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength, SocketTaskManager* pSocketTaskManager) {
    if (socketName == nullptr || ip == nullptr) {
        return false;
    }
    if (auto it = map_Sockets.find(socketName); it != map_Sockets.end()) { // 名称重复
        return false;
    }
    SocketCore* socketCore = SocketCore::createSocketAndListen(ip, port, socketName, ipv, socketT, waitingLength, pSocketTaskManager);
    if (socketCore == nullptr) {
        return false;
    }
    // 开启循环接收
    socketCore->cycRec();

    map_Sockets[socketName] = socketCore;
    return true;
}

bool SocketServer::removeSocket(char* socketName) {
    if (socketName == nullptr) {
        return false;
    }
    auto it = map_Sockets.find(socketName);
    if (it == map_Sockets.end()) {
        return false;
    }

    // 指针备份，防止迭代器失效无法访问
    char* pFirst = it->first;
    SocketCore* pSecond = it->second;

    try {
        map_Sockets.erase(it);
        delete[] pFirst;
        delete pSecond;
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}
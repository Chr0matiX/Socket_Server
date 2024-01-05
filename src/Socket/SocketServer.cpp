//
// Created by 86188 on 2023/12/26.
//

#include "SocketServer.h"

SocketServer::SocketServer() {
    m_pSocketTaskManager = new SocketTaskManager();
}

SocketServer::~SocketServer() {

}

bool SocketServer::addSocket(char* socketName, char* ip, int port, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength, SocketTaskManager* pSocketTaskManager) {
    if (socketName == nullptr || ip == nullptr) {
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
        delete[] it->first;
        delete it->second;
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}
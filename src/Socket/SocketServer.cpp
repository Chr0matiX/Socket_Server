//
// Created by 86188 on 2023/12/26.
//

#include "SocketServer.h"
#include <iostream>

// 静态成员的初始化
std::map<char*, SocketCore*> SocketServer::map_Sockets;
SocketTaskManager* SocketServer::m_pSocketTaskManager = nullptr;

SocketServer::SocketServer() { }

bool SocketServer::addSocket(char* socketName, char* ip, int port, Socket_Util::IPVersion ipv, Socket_Util::SocketType socketT, int waitingLength, SocketTaskManager* pSocketTaskManager) {
    if (socketName == nullptr || ip == nullptr) {
        std::cout << "[Warn]\tSocketServer::addSocket failed.\tip/socketName is nullptr.\n";
        return false;
    }
    if (auto it = map_Sockets.find(socketName); it != map_Sockets.end()) { // 名称重复
        std::cout << "[Warn]\tSocketServer::addSocket failed.\tDuplicate name.\tsocketName = " << socketName << std::endl;
        return false;
    }
    SocketCore* socketCore = SocketCore::createSocketAndListen(ip, port, socketName, ipv, socketT, waitingLength, pSocketTaskManager);
    if (socketCore == nullptr) {
        std::cout << "[Error]\tSocketServer::addSocket/SocketCore::createSocketAndListen failed.\n";
        return false;
    }
    // 开启循环接收
    socketCore->cycRec();

    // 添加到Map
    char* sName = Socket_Util::deepCopy(socketName); // 深拷贝避免内存泄漏
    map_Sockets[sName] = socketCore;

    std::cout << "[Info]\tSocketServer::addSocket succeed.\n";
    return true;
}

bool SocketServer::removeSocket(char* socketName) {
    if (socketName == nullptr) {
        std::cout << "[Warn]\tSocketServer::removeSocket failed.\tsocketName is nullptr.\n";
        return false;
    }
    auto it = map_Sockets.find(socketName);
    if (it == map_Sockets.end()) { // 未找到要删除的socket
        std::cout << "[Warn]\tSocketServer::removeSocket failed.\t" << socketName << " not found.\n";
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
        std::cout << "[Error]\tSocketServer::removeSocket failed.\tRelease exception.\n";
        return false;
    }
    std::cout << "[Info]\tSocketServer::removeSocket succeed.\n";
    return true;
}

bool SocketServer::initializeSocketServer() {
    if (m_pSocketTaskManager != nullptr) { // 初始化过了
        std::cout << "[Warn]\tSocketServer was initialized.\n";
        return false;
    }
    m_pSocketTaskManager = new SocketTaskManager();
    std::cout << "[Info]\tSocketServer initialize succeed.\n";
    return true;
}

bool SocketServer::deleteSocketServer() {
    for (auto& it : map_Sockets) { // 先将所有停止信号发下去
        it.second->m_stopSignal = true;
    }
    std::cout << "[Info]\tAll SocketCore/cycRec-thread stop.\n";

    for (auto& it : map_Sockets) { // 再一个个释放
        delete it.second;
        it.second = nullptr;
        delete[] it.first;
        //it.first = nullptr; // 不被允许，it.first的类型为char* const，所以无法修改指针本身的值
    }
    std::cout << "[Info]\tAll SocketCore release succeed.\n";

    map_Sockets.clear();
    delete m_pSocketTaskManager;
    m_pSocketTaskManager = nullptr;
    std::cout << "[Info]\tSocketServer release succeed.\n";
    return true;
}
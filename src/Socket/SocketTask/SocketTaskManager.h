//
// Created by caoch on 2023/12/30.
//

#ifndef SOCKET_SERVER_SOCKETTASKMANAGER_H
#define SOCKET_SERVER_SOCKETTASKMANAGER_H

#include <map>
#include <mutex>
#include "SocketTaskBase/SocketTaskBase.h"
#include "../Util.hpp"

class SocketTaskManager {
public:
    ~SocketTaskManager();
    // 添加任务，添加失败并不负责释放
    bool addSocketTask(char* taskName, SocketTaskBase* task);

    // 删除任务，并释放，删除失败不负责释放
    bool removeSocketTask(char* taskName);

    // 执行任务
    bool runSocketTask(char* taskName, char* arg);

private:
    std::map<char*, SocketTaskBase*, Socket_Util::mapCharPCmp> map_TaskIndex;
    std::mutex m_TaskIndexMapMutex;
};


#endif //SOCKET_SERVER_SOCKETTASKMANAGER_H

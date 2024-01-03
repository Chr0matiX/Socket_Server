//
// Created by caoch on 2023/12/30.
//

#include "SocketTaskManager.h"

bool SocketTaskManager::addSocketTask(char* taskName, SocketTaskBase* task) {
    if (taskName == nullptr || task == nullptr) return false;
    // 不重复
    if (auto it = map_TaskIndex.find(taskName); it != map_TaskIndex.end()) return false;

    m_TaskIndexMapMutex.lock();
    try {
        map_TaskIndex[taskName] = task;
    } catch (const std::exception& e) {
        m_TaskIndexMapMutex.unlock();
        return false;
    }
    m_TaskIndexMapMutex.unlock();
    return true;
}

bool SocketTaskManager::removeSocketTask(char* taskName) {
    // 存在键
    auto it = map_TaskIndex.find(taskName);
    if ( it == map_TaskIndex.end()) return false;
    m_TaskIndexMapMutex.lock();
    try {
        map_TaskIndex.erase(taskName); // 先操作容器
        // 如果没有抛出异常再释放
        delete[] it->first;
        delete[] it->second;
    } catch (const std::exception& e) {
        m_TaskIndexMapMutex.unlock();
        return false;
    }
    m_TaskIndexMapMutex.unlock();
    return true;
}

bool SocketTaskManager::runSocketTask(char* taskName, char* arg) {
    SocketTaskBase* socketTask = map_TaskIndex[taskName];
    socketTask->m_arg = arg;
    socketTask->run();
    if (socketTask->cptS == SocketTaskBase::cptStatus::exce) {
        std::exception e = socketTask->m_exception;
        socketTask->exceptionSafety(); // 发生异常，则执行异常安全函数
        return false;
    }
    return true;
}
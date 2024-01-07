//
// Created by caoch on 2023/12/30.
//

#include "SocketTaskManager.h"

SocketTaskManager::~SocketTaskManager() {
    // 怎么写都行，一个是迭代器指针，一个是键值对的引用
    //for (auto it = map_TaskIndex.begin(); it != map_TaskIndex.end(); ++it) {
    for (auto & it : map_TaskIndex) {
        delete[] it.first;
        delete it.second;
    }
}

bool SocketTaskManager::addSocketTask(char* taskName, SocketTaskBase* task) {
    if (taskName == nullptr || task == nullptr) return false;
    // 不重复
    try {
        auto it = map_TaskIndex.find(taskName);
        if (it != map_TaskIndex.end()) return false;
    } catch (const std::exception& e) {

    }

    char* tName = Socket_Util::deepCopy(taskName); // 深拷贝避免内存泄露
    m_TaskIndexMapMutex.lock();
    try {
        map_TaskIndex[tName] = task;
    } catch (const std::exception& e) {
        m_TaskIndexMapMutex.unlock();
        return false;
    }
    m_TaskIndexMapMutex.unlock();
    return true;
}

bool SocketTaskManager::removeSocketTask(char* taskName) {
    if (taskName == nullptr) {
        return false;
    }
    // 存在键
    auto it = map_TaskIndex.find(taskName);
    if ( it == map_TaskIndex.end()) return false;

    // 指针备份，防止迭代器失效无法访问
    char* pFirst = it->first;
    SocketTaskBase* pSecond = it->second;

    m_TaskIndexMapMutex.lock();
    try {
        map_TaskIndex.erase(it); // 先操作容器
        // 如果没有抛出异常再释放
        delete[] pFirst;
        delete pSecond;
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
        //std::exception e = socketTask->m_exception;
        socketTask->exceptionSafety(); // 发生异常，则执行异常安全函数
        return false;
    }
    return true;
}
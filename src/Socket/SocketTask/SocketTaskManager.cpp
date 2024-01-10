//
// Created by caoch on 2023/12/30.
//

#include "SocketTaskManager.h"
#include <iostream>

SocketTaskManager::~SocketTaskManager() {
    // 怎么写都行，一个是迭代器指针，一个是键值对的引用
    //for (auto it = map_TaskIndex.begin(); it != map_TaskIndex.end(); ++it) {
    for (auto & it : map_TaskIndex) {
        delete[] it.first;
        delete it.second;
    }
    std::cout << "[Info]\tSocketTaskManager release succeed.\n";
}

bool SocketTaskManager::addSocketTask(char* taskName, SocketTaskBase* task) {
    if (taskName == nullptr || task == nullptr) {
        std::cout << "[Warn]\tSocketTaskManager::addSocketTask failed.\ttaskName/task is nullptr";
        return false;
    }
    // 不重复
    auto it = map_TaskIndex.find(taskName);
    if (it != map_TaskIndex.end()) {
        std::cout << "[Warn]\tSocketTaskManager::addSocketTask failed.\tDuplicate name.\ttaskName = " << taskName << std::endl;
        return false;
    }

    char* tName = Socket_Util::deepCopy(taskName); // 深拷贝避免内存泄露
    m_TaskIndexMapMutex.lock();
    try {
        map_TaskIndex[tName] = task;
    } catch (const std::exception& e) {
        m_TaskIndexMapMutex.unlock();
        std::cout << "[Error]\tSocketTaskManager::addSocketTask failed.\t exception = " << e.what() << std::endl;
        return false;
    }
    m_TaskIndexMapMutex.unlock();
    std::cout << "[Info]\tSocketTaskManager::addSocketTask succeed.\n";
    return true;
}

bool SocketTaskManager::removeSocketTask(char* taskName) {
    if (taskName == nullptr) {
        std::cout << "[Warn]\tSocketTaskManager::removeSocketTask failed.\ttaskName is nullptr.\n";
        return false;
    }
    // 存在键
    auto it = map_TaskIndex.find(taskName);
    if ( it == map_TaskIndex.end()) {
        std::cout << "[Warn]\tSocketTaskManager::removeSocketTask failed.\t" << taskName << " not found.\n";
        return false;
    }

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
        std::cout << "[Error]\tSocketTaskManager::removeSocketTask failed.\tRelease exception.\n";
        return false;
    }
    m_TaskIndexMapMutex.unlock();
    std::cout << "[Info]\tSocketTaskManager::removeSocketTask succeed.\n";
    return true;
}

bool SocketTaskManager::runSocketTask(char* taskName, char* arg) {
    auto it = map_TaskIndex.find(taskName);
    if (it == map_TaskIndex.end()) {
        std::cout << "[Warn]\tSocketTaskManager::runSocketTask failed.\t" << taskName << " not found.\n";
        return false;
    }
    std::cout << "[Info]\tSocket-Task found:\t" << taskName << std::endl;

    SocketTaskBase* socketTask = it->second;
    socketTask->m_arg = arg;
    socketTask->run();
    if (socketTask->cptS == SocketTaskBase::cptStatus::exce) {
        //std::exception e = socketTask->m_exception;
        socketTask->exceptionSafety(); // 发生异常，则执行异常安全函数
        std::cout << "[Warn]\tSocketTaskManager::runSocketTask/TaskBase::run failed.\tTaskBase::run exception.\texception = " << socketTask->m_exception.what() << "\n";
        return false;
    }
    std::cout << "[Info]\tSocketTaskManager::runSocketTask succeed.\n";
    return true;
}
//
// Created by 86188 on 2023/12/28.
//

#include <iostream>
#include "ThreadPool.h"

ThreadPool::ThreadPool(int size) : m_ThreadPoolStop(false) {
    for (int i = 0; i < size; i++) {
        // 循环放入线程处理函数
        vec_WorkersThread.emplace_back(
                [this] {
                    while (1) {
                        TaskBase* task;
                        { // 锁的范围
                            std::unique_lock<std::mutex> lock(m_TasksQueueMutex);
                            // 等待通知，检查条件，重新上锁
                            m_condition.wait(lock, [this] {
                                return m_ThreadPoolStop || !que_Tasks.empty();
                            });
                            // 开始任务之前，先判断要不要终止
                            if (m_ThreadPoolStop && que_Tasks.empty()) {
                                return;
                            }
                            // 在锁的范围内进行临界量的处理
                            task = que_Tasks.front();
                            que_Tasks.pop();
                        } // unique_lock析构，解锁m_queueMutex
                        task->run();
                        // 发生异常调用异常安全函数
                        if (task->cptS == TaskBase::cptStatus::exce) {
                            //std::exception e = task->m_exception; // 获取异常
                            task->exceptionSafety();
                            std::cout << "[Error]\tThreadPool/TaskBask::run failed.\tThreadPool/TaskBase::run exception.\texception = " << task->m_exception.what() << std::endl;
                        }
                        delete task; // 释放
                        task = nullptr;
                    }
                });
    }
}

bool ThreadPool::addTask(TaskBase* task) {
    if (task == nullptr || m_ThreadPoolStop) {
        std::cout << "[Warn]\tThreadPool::addTask failed.\ttask is nullptr or ThreadPool is stop.\n";
        return false;
    }
    m_TasksQueueMutex.lock();
    try {
        que_Tasks.emplace(task); // 添加任务
    } catch (const std::exception& e) {
        m_TasksQueueMutex.unlock();
        std::cout << "[Error]\tThreadPool::addTask failed.\tThreadPool::addTask exception.\texception = " << e.what() << std::endl;
        return false;
    }
    m_TasksQueueMutex.unlock();
    m_condition.notify_one(); // 通知一个condition_variable
    std::cout << "[Info]\tThreadPool::addTask succeed.\n";
    return true;
}

ThreadPool::~ThreadPool() {
    m_ThreadPoolStop = true;
    m_condition.notify_all();

    // 等待队列中所有线程完成
    for (std::thread& workThread : vec_WorkersThread) {
        workThread.join();
    }
    std::cout << "[Info]\tThreadPool release succeed.\n";
}
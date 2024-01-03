//
// Created by 86188 on 2023/12/28.
//

#ifndef SOCKET_SERVER_THREADPOOL_H
#define SOCKET_SERVER_THREADPOOL_H


#include <vector>
#include <thread>
#include <queue>
#include <condition_variable>
#include "../Task/TaskBase.h"

class ThreadPool {
public:
    ThreadPool(int size);

    ~ThreadPool();

    // 添加任务到队列
    bool addTask(TaskBase* task);

private:
    std::vector<std::thread> vec_WorkersThread;
    std::queue<TaskBase*> que_Tasks;

    std::mutex m_TasksQueueMutex;
    std::condition_variable m_condition;

    // 线程池停止标志
    bool m_ThreadPoolStop;
};


#endif //SOCKET_SERVER_THREADPOOL_H

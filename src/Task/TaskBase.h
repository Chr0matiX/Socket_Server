//
// Created by 86188 on 2023/12/27.
//

#ifndef SOCKET_SERVER_TASKBASE_H
#define SOCKET_SERVER_TASKBASE_H

#include <exception>

class TaskBase {
public:
    enum cptStatus {
        running = 0,
        complete,
        exce
    } cptS;

    // 执行函数，纯虚
    virtual void run() = 0;

    // 异常安全函数
    virtual void exceptionSafety();

    // 虚析构
    virtual ~TaskBase() = default;

    // 发生的异常
    std::exception m_exception;

private:
};

#endif //SOCKET_SERVER_TASKBASE_H
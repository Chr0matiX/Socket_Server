#ifndef SOCKET_SERVER_GLOBAL_H
#define SOCKET_SERVER_GLOBAL_H

#include "Number/Number.h"
#include "ThreadPool/ThreadPool.h"

class SocketServerGlobal {
public:
    static Number *gl_pNumber;
    static ThreadPool *gl_pThreadPool;

    // 获取当前时间
    static char* getCurrentTime();
    // 显示当前时间
    static bool showCurrentTime();
};

#endif // SOCKET_SERVER_GLOBAL_H
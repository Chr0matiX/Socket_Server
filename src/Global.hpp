#ifndef SOCKET_SERVER_GLOBAL_HPP
#define SOCKET_SERVER_GLOBAL_HPP

#include "Number/Number.h"
#include "ThreadPool/ThreadPool.h"

namespace SocketServerGlobal {
    static Number *gl_pNumber;
    static ThreadPool *gl_pThreadPool;
}

#endif // SOCKET_SERVER_GLOBAL_HPP
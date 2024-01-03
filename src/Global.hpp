#ifndef SOCKET_SERVER_GLOBAL_HPP
#define SOCKET_SERVER_GLOBAL_HPP

#include "Number/Number.h"
#include "ThreadPool/ThreadPool.h"

namespace SocketServerGlobal {
    Number* gl_pNumber;
    ThreadPool* threadPool;
}



#endif // SOCKET_SERVER_GLOBAL_HPP
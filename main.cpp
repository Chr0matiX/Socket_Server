#include <iostream>
#include "src/Socket/Util.hpp"
#include "src/Global.hpp"
#include "src/Socket/SocketServer.h"
#include "src/Socket/SocketTask/UDTask/buildAddTask.h"

int main() {
    // 初始化Socket库
    if (!Socket_Util::initializeSocket()) {
        std::cout << "[Info]\tSocket initialize.";
        return -1;
    }
    // 初始化操作对象
    SocketServerGlobal::gl_pNumber = new Number(1000);
    // 初始化线程池
    SocketServerGlobal::gl_pThreadPool = new ThreadPool(6);

    // 先向服务器添加指令处理
    if (SocketServer::m_pSocketTaskManager->addSocketTask("testAdd", new buildAddTask())) {
        std::cout << "[Info]\tAdd Socket-Task succeed.";
    } else {
        std::cout << "[Warn]\tAdd Socket-Task failed.";
    }

    // 添加Socket配置、开启监听、开启循环接收
    if (SocketServer::addSocket("test1", "192.168.137.1", 11451, Socket_Util::IPVersion::v4, Socket_Util::SocketType::Stream, 5)) {
        std::cout << "[Info]\tAdd Socket succeed.";
    } else {
        std::cout << "[Warn]\tAdd Socket failed.";
    }

    char quite = '\0';
    while (quite != 'q') {
        std::cin >> quite;
    }
    delete SocketServerGlobal::gl_pThreadPool;
    delete SocketServerGlobal::gl_pNumber;
    WSACleanup();
    return 0;
}

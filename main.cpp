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
    // 初始化服务器
    SocketServer::initializeSocketServer();


    // 先向服务器添加指令处理
    if (SocketServer::m_pSocketTaskManager->addSocketTask("testAdd", new buildAddTask())) {
        std::cout << "[Info]\tAdd Socket-Task succeed.\n";
    } else {
        std::cout << "[Warn]\tAdd Socket-Task failed.\n";
    }

    // 添加Socket配置、开启监听、开启循环接收
    if (SocketServer::addSocket("test1", "127.0.0.1", 11451, Socket_Util::IPVersion::v4, Socket_Util::SocketType::Stream, 5)) {
        std::cout << "[Info]\tAdd Socket succeed.\n";
    } else {
        std::cout << "[Warn]\tAdd Socket failed.\n";
    }

    char quit = '\0';
    while (!(quit == 'q' || quit == 'Q')) {
        std::cin >> quit;
    }

    if (SocketServer::deleteSocketServer()) {
        std::cout << "[Info]\tDelete SocketServer succeed.\n";
    } else {
        std::cout << "[Warn]\tDelete SocketServer failed.\n";
    }
    delete SocketServerGlobal::gl_pThreadPool;
    delete SocketServerGlobal::gl_pNumber;
    WSACleanup();
    return 0;
}

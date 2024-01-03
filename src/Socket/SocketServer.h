//
// Created by 86188 on 2023/12/26.
//

#ifndef SOCKET_SERVER_SOCKETSERVER_H
#define SOCKET_SERVER_SOCKETSERVER_H

#include <vector>
#include <map>
#include "SocketCore.h"

class SocketServer {
public:
    // 创建Socket并加入到容器中

    // 接收连接，获取消息

private:
    // Socket容器
    std::map<char*, SocketCore> map_Sockets;
};


#endif //SOCKET_SERVER_SOCKETSERVER_H

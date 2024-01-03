#ifndef SOCKET_UTIL_HPP
#define SOCKET_UTIL_HPP

#include <functional>

namespace Socket_Util {
    // Internet Protocol Version enum
    enum IPVersion {
        v4 = 2,
        v6 = 23
    };

    // Socket Type enum
    enum SocketType {
        Stream = 1,     // 面向连接，可靠，双向字节流
        Dgram = 2       // 无连接，不可靠数据报
    };

    // 初始化Socket库，固定使用2.2
    static bool initalizeSocket() {
        WSADATA wsaData;    // 用于保存winsock库信息的结构体
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            return false;
        }
        return true;
    }

    // 分割逗号字符串
    static char** splStrByCom(char*) {

    }
}
#endif // SOCKET_UTIL_HPP
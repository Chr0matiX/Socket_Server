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
    char** splitStr(const char* arg){
        // 指针判空
        if (arg == nullptr) {
            return nullptr;
        }
        unsigned long long int cstrlen = strlen(arg);
        // 计算有多少个子串
        int count = 0;
        for (int i = 0; i < cstrlen; i++) {
            if (arg[i] == ',') { // 出现逗号
                count++;
            }
        }
        count++;
        char** args = new char*[count + 1];
        int argsIndex = 0;
        char buffer[1024];
        int buffIndex = 0;
        for (int i = 0; i < cstrlen + 1; i++) {
            if (arg[i] == ',' || arg[i] == '\0') { // 逗号结尾或文末的情况
                buffer[buffIndex] = '\0';
                char* tempStr = new char[strlen(buffer) + 1]; // 先开辟内存
                strcpy(tempStr, buffer); // 拷贝到开辟的内存中
                args[argsIndex] = tempStr; // 将开辟的内存存入char**
                argsIndex++;
                buffIndex = 0;
                continue;
            }
            buffer[buffIndex] = arg[i];
            buffIndex++;
        }
        args[argsIndex] = new char[1]; // 再加一个结尾符
        args[argsIndex][0] = '\0';
        return args;
    }
}
#endif // SOCKET_UTIL_HPP
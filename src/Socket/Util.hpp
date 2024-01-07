#ifndef SOCKET_UTIL_HPP
#define SOCKET_UTIL_HPP

#include <functional>
#include <winsock.h>

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
    static bool initializeSocket() {
        WSADATA wsaData;    // 用于保存winsock库信息的结构体
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            return false;
        }
        return true;
    }

    // 分割逗号字符串
    static char** splitStr(const char* arg){
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

    // 按照索引创建cstring
    static char* splitIndex(char* cstring, int start, int end) {
        int len = end - start;
        if (len < 0) {
            return nullptr;
        }
        char* rtn_string = new char[len + 1];
        for (int i = 0; i < len; ++i) {
            rtn_string[i] = cstring[start + i];
        }
        rtn_string[len] = '\0';
        return rtn_string;
    }

    static char* deepCopy(char* cstring) {
        char* rtn_cstring = new char[strlen(cstring) + 1];
        strcpy(rtn_cstring, cstring);
        return rtn_cstring;
    }

    struct mapCharPCmp {
        bool operator()(const char* cstring1, const char* cstring2) const {
            return strcmp(cstring1, cstring2) < 0;
        }
    };
}
#endif // SOCKET_UTIL_HPP
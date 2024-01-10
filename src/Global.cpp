#include <iostream>
#include <iomanip>
#include "Global.h"

Number* SocketServerGlobal::gl_pNumber;
ThreadPool* SocketServerGlobal::gl_pThreadPool;

char* SocketServerGlobal::getCurrentTime() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将时间点转换为 C 标准库的时间类型
    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::tm* timeInfo = std::localtime(&currentTime);

    char* rtn_Cstring = new char[24];
    std::strftime(rtn_Cstring, 24, "%Y-%m-%d %H:%M:%S", timeInfo);
    sprintf(rtn_Cstring + 19, ".%03lld", static_cast<long long>(milliseconds.count()));

    return rtn_Cstring;
}

bool SocketServerGlobal::showCurrentTime() {
    try {
        // 获取当前时间点
        auto now = std::chrono::system_clock::now();

        // 将时间点转换为 C 标准库的时间类型
        auto currentTime = std::chrono::system_clock::to_time_t(now);

        // 使用 std::put_time 将时间按指定格式输出
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        std::tm *timeInfo = std::localtime(&currentTime);

        // 输出格式化时间和毫秒
        std::cout << "Time = " << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3)
                  << std::setfill('0') << milliseconds.count() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[Error]\tSocketServerGlobal::showCurrentTime failed.\t exception = " << e.what() << std::endl;
        return false;
    }

    return true;
}
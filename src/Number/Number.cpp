//
// Created by 86188 on 2023/12/27.
//

#include "Number.h"
#include <iostream>

Number::Number(int num) : m_Num(num) { }

long long int Number::getNum() {
    return m_Num;
}

void Number::add(int num) {
    //std::lock_guard<std::mutex> lock(m_NumMutex); // 离开作用域解锁
    //std::unique_lock<std::mutex> lock(m_NumMutex); // 手动解锁
    m_NumMutex.lock(); // 更原始的方法
    try {
        m_Num += num;
    } catch (const std::exception& e) { // 此处引用，避免切片，指针也行，但是指针会花费内存 // 尽管对int的计算不会抛出异常
        m_NumMutex.unlock();  // 异常安全
        std::cout << "[Error]\tNumber::add failed.\texception = " << e.what() << "\t\tnum = " << num << std::endl;
    }
    m_NumMutex.unlock();
    std::cout << "[Info]\tNumber::add succeed.\tnum = " << num << std::endl;
}
//
// Created by 86188 on 2023/12/27.
//

#ifndef SOCKET_SERVER_NUMBER_H
#define SOCKET_SERVER_NUMBER_H

#include <mutex>

class Number {
public:
    long long int getNum();
    void add(int num);
    explicit Number(int num);
private:
    long long int m_Num;
    std::mutex m_NumMutex;
};


#endif //SOCKET_SERVER_NUMBER_H

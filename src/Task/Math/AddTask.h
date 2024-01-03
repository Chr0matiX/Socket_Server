//
// Created by 86188 on 2023/12/27.
//

#ifndef SOCKET_SERVER_ADDTASK_H
#define SOCKET_SERVER_ADDTASK_H


#include "../TaskBase.h"
#include "../../Number/Number.h"

class AddTask : public TaskBase {
public:
    void run() override;
    AddTask(std::function<void(Number*, int)> func, Number* pNum, int addNum);
private:
    std::function<void(Number*, int)> f_add;
    Number* m_pNum;
    int m_addNum;
};


#endif //SOCKET_SERVER_ADDTASK_H

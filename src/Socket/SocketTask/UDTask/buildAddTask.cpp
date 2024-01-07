//
// Created by caoch on 2023/12/30.
//

#include "buildAddTask.h"
#include "../../Util.hpp"
#include "../../../Task/Math/AddTask.h"
#include "../../../Global.hpp"
#include "../../../ThreadPool/ThreadPool.h"

static void f_add(Number* pNum, int addNum) {
    pNum->add(addNum);
}

void buildAddTask::run() {
    char** args = Socket_Util::splitStr(m_arg);
    if (args == nullptr) {
        return;
    }
    for (int i = 0; ; i++) {
        if (args[i][0] == '\0') {
            break;
        }
        char* endprt;
        int addNum = std::strtol(args[i], &endprt, 10);
        if (*endprt != '\0') {
            continue;
        }
        AddTask* addTask = new AddTask(
                f_add,
                SocketServerGlobal::gl_pNumber,
                addNum);
        SocketServerGlobal::gl_pThreadPool->addTask(addTask);
    }
    for (int i = 0; ; i++) {
        if (args[i][0] == '\0') {
            delete[] args[i];
            break;
        }
        delete[] args[i];
    }
}

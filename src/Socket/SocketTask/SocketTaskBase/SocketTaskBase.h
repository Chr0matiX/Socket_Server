//
// Created by caoch on 2023/12/30.
//

#ifndef SOCKET_SERVER_SOCKETTASKBASE_H
#define SOCKET_SERVER_SOCKETTASKBASE_H


#include "../../../Task/TaskBase.h"

class SocketTaskBase : public TaskBase {
public:
    char* m_arg;
    virtual ~SocketTaskBase();
};


#endif //SOCKET_SERVER_SOCKETTASKBASE_H

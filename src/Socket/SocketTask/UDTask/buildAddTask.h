//
// Created by caoch on 2023/12/30.
//

#ifndef SOCKET_SERVER_BUILDADDTASK_H
#define SOCKET_SERVER_BUILDADDTASK_H


#include "../SocketTaskBase/SocketTaskBase.h"

class buildAddTask : public SocketTaskBase {
public:
    void run() override;
};

#endif //SOCKET_SERVER_BUILDADDTASK_H

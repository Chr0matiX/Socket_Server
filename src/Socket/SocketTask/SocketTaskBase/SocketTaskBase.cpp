//
// Created by caoch on 2023/12/30.
//

#include "SocketTaskBase.h"

SocketTaskBase::~SocketTaskBase() noexcept {
    delete[] m_arg;
}
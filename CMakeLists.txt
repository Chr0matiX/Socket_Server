cmake_minimum_required(VERSION 3.25)
project(Socket_Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Socket_Server
        main.cpp

        src/Socket/Util.hpp
        src/Global.hpp

        src/Socket/SocketCore.cpp
        src/Socket/SocketCore.h

        src/Socket/SocketServer.cpp
        src/Socket/SocketServer.h

        src/Task/TaskBase.cpp
        src/Task/TaskBase.h

        src/Number/Number.cpp
        src/Number/Number.h

        src/Task/Math/AddTask.cpp
        src/Task/Math/AddTask.h

        src/ThreadPool/ThreadPool.cpp
        src/ThreadPool/ThreadPool.h

        src/Socket/SocketTask/SocketTaskBase/SocketTaskBase.cpp
        src/Socket/SocketTask/SocketTaskBase/SocketTaskBase.h

        src/Socket/SocketTask/SocketTaskManager.cpp
        src/Socket/SocketTask/SocketTaskManager.h

        src/Socket/SocketTask/UDTask/buildAddTask.h
        src/Socket/SocketTask/UDTask/buildAddTask.cpp
)

target_link_libraries(Socket_Server ws2_32)
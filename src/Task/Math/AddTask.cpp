//
// Created by 86188 on 2023/12/27.
//

#include "AddTask.h"
#include <utility>
#include <thread>
#include <iostream>

void AddTask::run() {
    cptS = cptStatus::running;
    try {
        f_add(m_pNum, m_addNum);
    } catch (const std::exception& e) {
        m_exception = e;
        cptS = cptStatus::exce;
        std::cout << "[Warn]\tAddTask::run failed.\tAdd exception.\n";
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 休眠1秒，模拟耗时操作
    cptS = cptStatus::complete;
    std::cout << "[Info]\tAddTask::run succeed.\n";
}

AddTask::AddTask(std::function<void(Number*, int)> func, Number* pNum, int addNum) : f_add(std::move(func)), m_pNum(pNum), m_addNum(addNum) { }
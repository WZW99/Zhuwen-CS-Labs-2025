#include "Handler.h"
#include <iostream>
#include "Tasks/Tasks.h"

namespace {
    const size_t kTasksCount = 9;
    const size_t kStreamIgnoreSymbols = 256;
} // namespace

void Handler::InteractiveModeInit() {
    Task* tasks[kTasksCount] = {new FirstTask(), new SecondTask(), new ThirdTask(),
                              new FourthTask(), new FifthTask(), new SixthTask(),
                              new SeventhTask(), new EighthTask(), new NinethTask()};

    for (Task* task : tasks) {
        task->Init();
        delete task;
        std::cout << "\nВведите, чтобы продолжить... ";
        std::cin.get();
        std::cin.ignore(kStreamIgnoreSymbols, '\n');
        std::cout << '\n';
    }
}

void Handler::DemoModeInit() {
    NinethTask task;
    task.Init();
}

Handler::Handler(bool isInteractive) : isInteractive(isInteractive) {}

Handler::~Handler() = default;

void Handler::Init() {
    this->isInteractive ? this->InteractiveModeInit() : this->DemoModeInit();
}

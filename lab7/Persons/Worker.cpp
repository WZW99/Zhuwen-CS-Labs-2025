#include "Worker.h"

Worker::Worker() {
    std::cout << "Worker()\n";
}

Worker::Worker(const char* name, size_t salary, double efficiency,
               double teamWork, double stamina, double discipline)
    : Person(name, salary, efficiency, teamWork),
      stamina(stamina), discipline(discipline) {
    std::cout << "Worker(...)\n";
}

Worker::~Worker() {
    std::cout << "~Worker()\n";
}

void Worker::Show(std::ostream& stream) const {
    stream << "Имя: " << name << "; Зарплата: " << salary
           << "; Работоспособность: " << efficiency
           << "; Работа в команде: " << teamWork
           << "; Выносливость: " << stamina
           << "; Дисциплина: " << discipline;
}

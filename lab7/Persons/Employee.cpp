#include "Employee.h"

Employee::Employee() {
    std::cout << "Employee()\n";
}

Employee::Employee(const char* name, size_t salary, double efficiency,
                   double teamWork, double stressResistance, double initiative)
    : Person(name, salary, efficiency, teamWork),
      stressResistance(stressResistance), initiative(initiative) {
    std::cout << "Employee(...)\n";
}

Employee::~Employee() {
    std::cout << "~Employee()\n";
}

void Employee::Show(std::ostream& stream) const {
    stream << "Имя: " << name << "; Зарплата: " << salary
           << "; Работоспособность: " << efficiency
           << "; Работа в команде: " << teamWork
           << "; Стрессоустойчивость: " << stressResistance
           << "; Инициативность: " << initiative;
}

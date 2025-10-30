#include "Engineer.h"

Engineer::Engineer() {
    std::cout << "Engineer()\n";
}

Engineer::Engineer(const char* name, size_t salary, double efficiency,
                   double teamWork, double analyticalThinking, double communicationSkills)
    : Person(name, salary, efficiency, teamWork),
      analyticalThinking(analyticalThinking),
      communicationSkills(communicationSkills) {
    std::cout << "Engineer(...)\n";
}

Engineer::~Engineer() {
    std::cout << "~Engineer()\n";
}

void Engineer::Show(std::ostream& stream) const {
    stream << "Имя: " << name << "; Зарплата: " << salary
           << "; Работоспособность: " << efficiency
           << "; Работа в команде: " << teamWork
           << "; Аналитическое мышление: " << analyticalThinking
           << "; Коммуникабельность: " << communicationSkills;
}

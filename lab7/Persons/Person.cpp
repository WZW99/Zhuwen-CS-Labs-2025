#include "Person.h"

Person::Person() {
    std::cout << "Person()\n";
}

Person::Person(const char* name, size_t salary,
               double efficiency, double teamWork)
    : salary(salary), efficiency(efficiency), teamWork(teamWork) {
    SetName(name);
    std::cout << "Person(...)\n";
}

Person::Person(const Person& person) {
    SetName(person.name);
    salary = person.salary;
    efficiency = person.efficiency;
    teamWork = person.teamWork;
    std::cout << "Person(const Person&)\n";
}

Person::~Person() {
    delete[] name;
    std::cout << "~Person()\n";
}

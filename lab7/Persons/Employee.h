#pragma once
#include "Person.h"

class Employee : public Person {
protected:
    double stressResistance = 0.0;
    double initiative = 0.0;

public:
    Employee();
    Employee(const char* name, size_t salary, double efficiency,
             double teamWork, double stressResistance, double initiative);
    ~Employee() override;
    void Show(std::ostream& stream) const override;

    friend std::istream& operator>>(std::istream& stream, Employee& emp) {
        stream >> static_cast<Person&>(emp);
        std::cout << "Стрессоустойчивость: "; stream >> emp.stressResistance;
        std::cout << "Инициативность: "; stream >> emp.initiative;
        return stream;
    }
};

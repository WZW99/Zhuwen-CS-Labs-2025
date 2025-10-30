#pragma once
#include "Person.h"

class Worker : public Person {
protected:
    double stamina = 0.0;
    double discipline = 0.0;

public:
    Worker();
    Worker(const char* name, size_t salary, double efficiency,
           double teamWork, double stamina, double discipline);
    ~Worker() override;
    void Show(std::ostream& stream) const override;

    friend std::istream& operator>>(std::istream& stream, Worker& worker) {
        stream >> static_cast<Person&>(worker);
        std::cout << "Выносливость: "; stream >> worker.stamina;
        std::cout << "Дисциплина: "; stream >> worker.discipline;
        return stream;
    }
};

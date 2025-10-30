#pragma once
#include <iostream>
#include <cstring>

class Person {
protected:
    char* name = nullptr;
    size_t salary = 0;
    double efficiency = 0.0;
    double teamWork = 0.0;

    void SetName(const char* name) {
        if (this->name) delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

public:
    Person();
    Person(const char* name, size_t salary, double efficiency, double teamWork);
    Person(const Person& person);
    virtual ~Person();

    virtual void Show(std::ostream& stream) const = 0;

    friend std::ostream& operator<<(std::ostream& stream, const Person& person) {
        person.Show(stream);
        return stream;
    }

    friend std::istream& operator>>(std::istream& stream, Person& person) {
        char buffer[256];
        std::cout << "Имя: "; stream >> buffer;
        person.SetName(buffer);
        std::cout << "Зарплата: "; stream >> person.salary;
        std::cout << "Работоспособность: "; stream >> person.efficiency;
        std::cout << "Работа в команде: "; stream >> person.teamWork;
        return stream;
    }
};

#pragma once
#include "Person.h"

class Engineer : public Person {
protected:
    double analyticalThinking = 0.0;
    double communicationSkills = 0.0;

public:
    Engineer();
    Engineer(const char* name, size_t salary, double efficiency,
             double teamWork, double analyticalThinking, double communicationSkills);
    ~Engineer() override;
    void Show(std::ostream& stream) const override;

    friend std::istream& operator>>(std::istream& stream, Engineer& eng) {
        stream >> static_cast<Person&>(eng);
        std::cout << "Аналитическое мышление: "; stream >> eng.analyticalThinking;
        std::cout << "Коммуникабельность: "; stream >> eng.communicationSkills;
        return stream;
    }
};

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class fraction {
private:
    int numerator;
    int denominator;
    int whole;

    void simplify();
    void normalize();

public:
    fraction();
    fraction(int num, int denom = 1);
    fraction(double value);
    fraction(const char* str);
    fraction(const fraction& other);

    fraction operator+(const fraction& other) const;
    fraction operator+(int value) const;
    fraction operator+(double value) const;
    fraction& operator+=(const fraction& other);
    fraction& operator+=(int value);
    fraction& operator+=(double value);

    friend fraction operator+(int value, const fraction& fr);
    friend fraction operator+(double value, const fraction& fr);
    friend std::ostream& operator<<(std::ostream& os, const fraction& fr);
    friend std::istream& operator>>(std::istream& is, fraction& fr);
};

void Run();

#endif

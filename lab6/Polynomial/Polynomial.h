#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "Term.h"
#include <vector>

class Polynomial {
private:
    std::vector<Term> terms;
    void combineLikeTerms();

public:
    Polynomial() = default;
    Polynomial(int c) { if (c != 0) terms.emplace_back(c); }
    Polynomial(const Term& t) { terms.push_back(t); }

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    friend Polynomial operator+(const Polynomial& a, const Polynomial& b);
    friend Polynomial operator*(const Polynomial& a, const Polynomial& b);

    friend std::istream& operator>>(std::istream& is, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};

#endif

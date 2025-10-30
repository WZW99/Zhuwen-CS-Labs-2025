#ifndef TERM_H
#define TERM_H
#include <iostream>

class Term {
private:
    int coeff;
    int exp;

public:
    Term() : coeff(0), exp(0) {}
    Term(int c, int e = 0) : coeff(c), exp(e) {}

    int getCoeff() const { return coeff; }
    int getExp() const { return exp; }

    bool operator==(const Term& other) const { return exp == other.exp; }
    Term operator+(const Term& other) const {
        if (exp != other.exp) throw std::invalid_argument("Mismatched exponents");
        return Term(coeff + other.coeff, exp);
    }

    friend std::istream& operator>>(std::istream& is, Term& t);
    friend std::ostream& operator<<(std::ostream& os, const Term& t);
};

#endif

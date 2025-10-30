#include "Polynomial.h"
#include <algorithm>
#include <sstream>

void Polynomial::combineLikeTerms() {
    std::sort(terms.begin(), terms.end(), [](const Term& a, const Term& b) {
        return a.getExp() > b.getExp();
    });

    std::vector<Term> result;
    for (const Term& t : terms) {
        if (!result.empty() && result.back() == t) {
            result.back() = result.back() + t;
        } else {
            result.push_back(t);
        }
    }

    terms.clear();
    for (const Term& t : result) {
        if (t.getCoeff() != 0 || t.getExp() == 0) terms.push_back(t);
    }
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    terms.insert(terms.end(), other.terms.begin(), other.terms.end());
    combineLikeTerms();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    std::vector<Term> result;
    for (const Term& a : terms) {
        for (const Term& b : other.terms) {
            result.emplace_back(a.getCoeff() * b.getCoeff(), a.getExp() + b.getExp());
        }
    }
    terms = result;
    combineLikeTerms();
    return *this;
}

Polynomial operator+(const Polynomial& a, const Polynomial& b) {
    Polynomial result = a;
    result += b;
    return result;
}
Polynomial operator*(const Polynomial& a, const Polynomial& b) {
    Polynomial result = a;
    result *= b;
    return result;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    p.terms.clear();
    std::string line;
    std::getline(is >> std::ws, line);
    std::istringstream ss(line);
    Term t;
    char op = '+';

    while (ss >> t) {
        if (op == '-') t = Term(-t.getCoeff(), t.getExp());
        p.terms.push_back(t);
        ss >> op;
    }
    p.combineLikeTerms();
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.terms.empty()) return os << "0";
    bool first = true;
    for (const Term& t : p.terms) {
        if (t.getCoeff() == 0) continue;
        if (!first) os << (t.getCoeff() > 0 ? " + " : " - ");
        else if (t.getCoeff() < 0) os << "-";
        first = false;
        int abs_coeff = std::abs(t.getCoeff());
        if (abs_coeff != 1 || t.getExp() == 0) os << abs_coeff;
        if (t.getExp() > 0) {
            os << "x";
            if (t.getExp() > 1) os << "^" << t.getExp();
        }
    }
    return os;
}

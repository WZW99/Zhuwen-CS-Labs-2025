#include "Term.h"
#include <sstream>
#include <string>

std::istream& operator>>(std::istream& is, Term& t) {
    std::string token;
    is >> token;

    t = Term();
    int sign = 1;
    size_t pos = 0;
    if (token[pos] == '-') { sign = -1; ++pos; }
    else if (token[pos] == '+') { ++pos; }

    size_t x_pos = token.find('x', pos);
    std::string coeff_str = (x_pos == std::string::npos) ? token.substr(pos) : token.substr(pos, x_pos - pos);
    t.coeff = coeff_str.empty() ? 1 : std::stoi(coeff_str);
    t.coeff *= sign;

    if (x_pos != std::string::npos) {
        size_t caret = token.find('^', x_pos);
        t.exp = (caret != std::string::npos) ? std::stoi(token.substr(caret + 1)) : 1;
    } else {
        t.exp = 0;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Term& t) {
    if (t.coeff == 0) return os << "0";
    if (t.coeff == -1 && t.exp != 0) os << "-";
    else if (t.coeff != 1 || t.exp == 0) os << t.coeff;

    if (t.exp > 0) {
        os << "x";
        if (t.exp > 1) os << "^" << t.exp;
    }
    return os;
}

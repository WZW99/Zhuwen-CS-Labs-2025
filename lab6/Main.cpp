#include "Polynomial/Polynomial.h"
#include <iostream>
#include <limits>

int main() {
    Polynomial p1, p2;
    std::cout << "Enter Polynomial 1 (e.g., 3x^2 - x + 4): ";
    std::cin >> p1;
    std::cout << "Enter Polynomial 2 (e.g., 2x^2 + 6x - 2): ";
    std::cin >> p2;

    std::cout << "\nP1 = " << p1 << "\n";
    std::cout << "P2 = " << p2 << "\n";
    std::cout << "P1 + P2 = " << (p1 + p2) << "\n";
    std::cout << "P1 * P2 = " << (p1 * p2) << "\n";
    return 0;
}

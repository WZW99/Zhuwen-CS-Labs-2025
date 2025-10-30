#include "fraction.h"
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <limits>

const int N_DEC = 4;

void ShowMainMenu(){
    std::cout << "\n-------------------------------\n";
    std::cout << "\n1.Demo";
    std::cout << "\n2.Interactive";
    std::cout << "\n3.Exit\n";
    std::cout << "\n-------------------------------\n";
    std::cout << "Enter choice : ";
}


int ReadChoice(){
    int choice{};
    std::cin >> choice;
    return choice;
}

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

fraction::fraction() : numerator(0), denominator(1), whole(0) {}

fraction::fraction(int num, int denom) : numerator(num), denominator(denom), whole(0) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    simplify();
    normalize();
}

fraction::fraction(double value) {
    whole = static_cast<int>(value);
    double fractional = value - whole;

    denominator = 1;
    for (int i = 0; i < N_DEC; ++i) {
        denominator *= 10;
    }


    numerator = round(fractional * denominator);
    simplify();
    normalize();
}

fraction::fraction(const char* str) {
    int sign = 1;
    int w = 0, n = 0, d = 1;
    bool hasFraction = false;
    bool hasWhole = false;

    const char* p = str;

    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    while (*p >= '0' && *p <= '9') {
        w = w * 10 + (*p - '0');
        hasWhole = true;
        p++;
    }

    if (*p == ' ') {
        p++;
        while (*p >= '0' && *p <= '9') {
            n = n * 10 + (*p - '0');
            p++;
        }
        if (*p == '/') {
            p++;
            d = 0;
            while (*p >= '0' && *p <= '9') {
                d = d * 10 + (*p - '0');
                p++;
            }
            hasFraction = true;
        }
    } else if (*p == '/') {
        p++;
        n = w;
        w = 0;
        hasWhole = false;
        d = 0;
        while (*p >= '0' && *p <= '9') {
            d = d * 10 + (*p - '0');
            p++;
        }
        hasFraction = true;
    }

    if (d == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    if (!hasFraction && hasWhole) {
        whole = sign * w;
        numerator = 0;
        denominator = 1;
    } else {
        whole = sign * w;
        numerator = sign * n;
        denominator = d;
    }

    simplify();
    normalize();
}


fraction::fraction(const fraction& other)
    : numerator(other.numerator), denominator(other.denominator), whole(other.whole) {}

void fraction::simplify() {
    if (denominator == 0) {
        throw std::runtime_error("Denominator is zero");
    }
    if (numerator == 0) {
        denominator = 1;
        return;
    }

    int common = gcd(numerator, denominator);
    numerator /= common;
    denominator /= common;
}

void fraction::normalize() {
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }

    if (abs(numerator) >= denominator) {
        whole += numerator / denominator;
        numerator = numerator % denominator;
    }

    if (whole != 0 && numerator < 0) {
        numerator = -numerator;
    }
}

fraction fraction::operator+(const fraction& other) const {
    fraction result;
    result.numerator = (whole * denominator + numerator) * other.denominator +
                      (other.whole * other.denominator + other.numerator) * denominator;
    result.denominator = denominator * other.denominator;
    result.simplify();
    result.normalize();
    return result;
}

fraction fraction::operator+(int value) const {
    return *this + fraction(value);
}

fraction fraction::operator+(double value) const {
    return *this + fraction(value);
}

fraction& fraction::operator+=(const fraction& other) {
    *this = *this + other;
    return *this;
}

fraction& fraction::operator+=(int value) {
    *this = *this + fraction(value);
    return *this;
}

fraction& fraction::operator+=(double value) {
    *this = *this + fraction(value);
    return *this;
}

fraction operator+(int value, const fraction& fr) {
    return fr + value;
}


fraction operator+(double value, const fraction& fr) {
    return fr + value;
}

std::ostream& operator<<(std::ostream& os, const fraction& fr) {
    if (fr.whole != 0) {
        os << fr.whole;
        if (fr.numerator != 0) {
            os << " " << fr.numerator << "/" << fr.denominator;
        }
    } else {
        if (fr.numerator != 0) {
            os << fr.numerator << "/" << fr.denominator;
        } else {
            os << "0";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, fraction& fr) {
    const int BUFFER_SIZE = 256;
    is >> std::ws;
    char buffer[BUFFER_SIZE];
    is.getline(buffer, BUFFER_SIZE);

    try {
        fr = fraction(buffer);
    } catch (const std::exception& e) {
        is.setstate(std::ios::failbit);
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return is;
}
void demo() {
    std::cout << "=== Demo ===" << std::endl;

    fraction fr1(10, 14);
    fraction fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;

    fraction fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;

    double dbl = -1.25;
    fraction f = dbl;
    std::cout << "f=" << f << std::endl;

    fraction x = "3/4";
    fraction y;
    std::cout << "x=" << x << std::endl;

    y = x + fr1;
    std::cout << "y=" << y << std::endl;

    y += x;
    std::cout << "y=" << y << std::endl;

    f += dbl / 2;
    std::cout << "f=" << f << std::endl;

    y = x + dbl;
    std::cout << "y=" << y << std::endl;

    y = dbl + y;
    std::cout << "y=" << y << std::endl;

    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;

    y = i + x;
    std::cout << "y=" << y << std::endl;
}

void Run();

void RunUserChoice(int choice) {
    if (choice == 2) {
        char ans = 'y';
        while (ans == 'y') {
            fraction a;
            std::cout << "Enter a fraction please: ";

            if (!(std::cin >> a)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Try again.\n";
                continue;
            }

            std::cout << "You entered: a = " << a << "\n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Continue? (y/n): ";
            std::cin >> ans;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        Run();
    }else{
        return;
    }
}

void Run(){
    ShowMainMenu();
    RunUserChoice(ReadChoice());
}

#include <cmath>
#include <iostream>
#include "mymath.h"

namespace {
    int rootFinder(double a, double b, double c, double &x1, double &x2) {
        if (a == 0) {
            if (b == 0) {
                if (c == 0) {
                    return 0;
                } else {
                    return 1;
                }
            } else {
                x1 = -c / b;
                return 2;
            }
        }

        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return 1;
        }
        if (discriminant == 0) {
            x1 = -b / (2 * a);
            return 2;
        }
        x1 = (-b - sqrt(discriminant)) / (2 * a);
        x2 = (-b + sqrt(discriminant)) / (2 * a);
        return 3;
    }

    void InputCoefficients( double &a, double &b, double &c) {
        std::cout << "Введите коэффициенты при квадратном уравнении: ax^2 + bx + c" << std::endl;
        std::cout << "Введите коэффициент a при старшем члене" << std::endl;
        std::cin >> a;
        std::cout << "Введите коэффициент b" << std::endl;
        std::cin >> b;
        std::cout << "Введите свободный член c" << std::endl;
        std::cin >> c;
    }

    void PrintRoots( int result, double x1, double x2) {
        switch (result) {
            case 0:
            std::cout << "Бесконечное множество решений" << std::endl;
            break;
            case 1:
            std::cout << "Нет корней" << std::endl;
            break;
            case 2:
            std::cout << "Уравнение имеет единственное решение x = " << x1 << std::endl;
            break;
            case 3:
            std::cout << "Уравнение имеет 2 решения x1 = " << x1 << ", x2 = " << x2 <<std::endl;
            break;
            default:
            std::cout << "Ошибка" << std::endl;
        }
    }
}

namespace mymath {
    void RunRootFinder() {
        double a;
        double b;
        double c;
        InputCoefficients(a, b, c);

        double root1;
        double root2;
        int result = rootFinder(a, b, c, root1, root2);

        PrintRoots(result, root1, root2);
    }
}

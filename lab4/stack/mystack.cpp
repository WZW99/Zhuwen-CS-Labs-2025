#include "mystack.h"
#include <limits>
#include <cmath>
#include <iostream>
template<class DATA>
void Multipliers(int n, MyStack<DATA>& stack) {
    if (n == 0 || n == 1) {
        stack.push(n);
        return;
    }

    if (n < 0) {
        stack.push(-1);
        n = -n;
    }

    while (n % 2 == 0) {
        stack.push(2);
        n /= 2;
    }

    for (int i = 3; i <= std::sqrt(n); i += 2) {
        while (n % i == 0) {
            stack.push(i);
            n /= i;
        }
    }

    if (n > 2) {
        stack.push(n);
    }
}

void printFactors(int number, MyStack<int>& stack) {
    std::cout << number << " = ";
    MyStack<int> tempStack = stack;
    bool first = true;
    while (!tempStack.empty()) {
        if (!first) std::cout << " * ";
        std::cout << tempStack.top_inf();
        tempStack.pop();
        first = false;
    }
    std::cout << std::endl;

    MyStack<int> reversedStack;
    tempStack = stack;
    while (!tempStack.empty()) {
        reversedStack.push(tempStack.top_inf());
        tempStack.pop();
    }

    std::cout << number << " = ";
    first = true;
    while (!reversedStack.empty()) {
        if (!first) std::cout << " * ";
        std::cout << reversedStack.top_inf();
        reversedStack.pop();
        first = false;
    }
    std::cout << std::endl << std::endl;
}

void interactiveMode() {
    int number;
    while (true) {
        std::cout << "Enter a number to factorize (0 to exit): ";
        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter an integer.\n";
            continue;
        }

        if (number == 0) break;

        MyStack<int> stack;
        Multipliers(number, stack);
        printFactors(number, stack);
    }
    std::cout << "Exiting program...\n";
}

void demoMode() {
    int number = 3960;
    MyStack<int> stack;
    Multipliers(number, stack);
    printFactors(number, stack);
}

void Run() {
    char ans = 'y';
    while(ans == 'y'){
        int choice;
        std::cout << "=== Prime Factorization using Stack ===\n";
        std::cout << "1. Interactive Mode (Enter numbers manually)\n";
        std::cout << "2. Demo Mode (Fixed example: 3960)\n";
        std::cout << "Enter your choice (1 or 2): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cerr << "Invalid choice! Exiting...\n";
            return ;
        }

        switch (choice) {
            case 1: interactiveMode(); break;
            case 2: demoMode(); break;
            default: std::cerr << "Invalid choice! Exiting...\n";
        }

        std::cout << "Do you want to keep running (y/n) : ";
        std::cin >> ans;
    }

}

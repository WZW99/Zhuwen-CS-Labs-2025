#include "Handler.h"
#include "Persons/Employee.h"
#include "Persons/Engineer.h"
#include "Persons/Person.h"
#include "Persons/Worker.h"
#include "Stack/Stack.h"

namespace {
    const size_t kStreamIgnoreSymbols = 256;

    void NavigationItemsPrint() {
        std::cout << "Выберите действие:\n"
                  << "a - Вывести\nb - Добавить\n"
                  << "c - Удалить (Pop)\nd - Очистить\nq - Выход\n\nДействие: ";
    }

    void PrintStack(Stack<Person*>& stack) {
        Stack<Person*> tempStack = stack;
        while (!tempStack.Empty()) {
            std::cout << *tempStack.Top() << '\n';
            tempStack.Pop();
        }
    }

    void AddToStack(Stack<Person*>& stack) {
        size_t objectIndex = 0;
        std::cout << "Тип объекта (1-Worker, 2-Employee, 3-Engineer): ";
        std::cin >> objectIndex;

        switch (objectIndex) {
            case 1: {
                auto* worker = new Worker;
                std::cin >> *worker;
                stack.Push(worker);
                break;
            }
            case 2: {
                auto* employee = new Employee;
                std::cin >> *employee;
                stack.Push(employee);
                break;
            }
            case 3: {
                auto* engineer = new Engineer;
                std::cin >> *engineer;
                stack.Push(engineer);
                break;
            }
            default: std::cout << "Ошибка!\n";
        }
    }

    void PopFromStack(Stack<Person*>& stack) {
        if (!stack.Empty()) {
            delete stack.Top();
            stack.Pop();
        }
    }

    void ClearStack(Stack<Person*>& stack) {
        while (!stack.Empty()) {
            delete stack.Top();
            stack.Pop();
        }
    }
}

void Handler::InteractiveModeInit() {
    Stack<Person*> stack;
    char userAnswer = ' ';
    while (userAnswer != 'q') {
        NavigationItemsPrint();
        std::cin >> userAnswer;
        std::cin.ignore(kStreamIgnoreSymbols, '\n');

        switch (userAnswer) {
            case 'a': PrintStack(stack); break;
            case 'b': AddToStack(stack); break;
            case 'c': PopFromStack(stack); break;
            case 'd': ClearStack(stack); break;
            case 'q': std::cout << "\nВыход!\n"; break;
            default: std::cout << "Неверное действие!\n";
        }
        std::cout << '\n';
    }
}

void Handler::DemoModeInit() {
    Stack<Person*> stack;
    stack.Push(new Worker("Andy", 567, 4, 7, 1, 1));
    stack.Push(new Engineer("Sam", 45327, 1, 7, 4, 2));
    stack.Push(new Employee("Tom", 754, 5, 3, 2, 4));

    std::cout << '\n';
    PrintStack(stack);
    std::cout << '\n';
    ClearStack(stack);
}

Handler::Handler(bool isInteractive) : isInteractive(isInteractive) {}
Handler::~Handler() = default;

void Handler::Init() {
    isInteractive ? InteractiveModeInit() : DemoModeInit();
}

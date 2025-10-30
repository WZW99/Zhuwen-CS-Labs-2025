#include <iostream>
#include "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/planet/planet.h"
#include "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/filmoteka/filmoteka.h"


int main() {
    int userChoice{};
    std::cout << "Do you want to work with planets or films? (1/2)\nEnter a number: ";
    std::cin >> userChoice;
    switch (userChoice) {
        case 1:
            planetApp::StartApplication();
            break;
        case 2:
            FilmApp::RunApplication();
            break;
        default:
            std::cout << "Option " << userChoice << " is not available, please enter a number between 1 and 2!\n";
            break;
    }

return 0;
}

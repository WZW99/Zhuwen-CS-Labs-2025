#include <iostream>
#include "/home/zhuwen/Zhuwen-CS-Labs-2025/lab5/myvector/MySet.h"

int main() {
    MySet<int> set1;
    set1.add_element(5);
    set1.add_element(3);
    set1.add_element(7);
    set1.add_element(3);

    MySet<int> set2;
    set2.add_element(3);
    set2.add_element(8);

    std::cout << "Set1: " << set1 << std::endl;
    std::cout << "Set2: " << set2 << std::endl;

    MySet<int> union_set = set1 + set2;
    MySet<int> intersection_set = set1 * set2;
    MySet<int> difference_set = set1 - set2;

    std::cout << "Union: " << union_set << std::endl;
    std::cout << "Intersection: " << intersection_set << std::endl;
    std::cout << "Difference (set1 - set2): " << difference_set << std::endl;

    return 0;
}

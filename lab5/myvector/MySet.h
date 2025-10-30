#ifndef MYSET_H
#define MYSET_H

#include "MyVector.h"
#include <algorithm>

template <typename T>
class MySet : public MyVector<T> {
    using MyVector<T>::vec;

    int q_find(const T& element) const {
        int left = 0, right = static_cast<int>(vec.size) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (vec.data[mid] == element) return mid;
            if (vec.data[mid] < element) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    void sort() {
        std::sort(vec.data, vec.data + vec.size);
    }

public:
    MySet() : MyVector<T>() {}
    MySet(const MySet& other) : MyVector<T>(other) {}

    bool is_element(const T& element) const {
        return q_find(element) != -1;
    }

    void add_element(const T& element) override {
        if (!is_element(element)) {
            MyVector<T>::add_element(element);
            sort();
        }
    }

    void delete_element(const T& element) {
        int index = q_find(element);
        if (index != -1) {
            MyVector<T>::delete_element(static_cast<size_t>(index));
        }
    }

    MySet& operator+=(const MySet& other) {
        for (size_t i = 0; i < other.vec.size; ++i) {
            add_element(other.vec.data[i]);
        }
        return *this;
    }

    MySet& operator-=(const MySet& other) {
        for (size_t i = 0; i < other.vec.size; ++i) {
            delete_element(other.vec.data[i]);
        }
        return *this;
    }

    MySet& operator*=(const MySet& other) {
        MySet<T> temp;
        for (size_t i = 0; i < vec.size; ++i) {
            if (other.is_element(vec.data[i])) {
                temp.add_element(vec.data[i]);
            }
        }
        *this = temp;
        return *this;
    }

    friend MySet operator+(const MySet& a, const MySet& b) {
        MySet result = a;
        result += b;
        return result;
    }

    friend MySet operator-(const MySet& a, const MySet& b) {
        MySet result = a;
        result -= b;
        return result;
    }

    friend MySet operator*(const MySet& a, const MySet& b) {
        MySet result = a;
        result *= b;
        return result;
    }

    friend bool operator==(const MySet& a, const MySet& b) {
        if (a.vec.size != b.vec.size) return false;
        for (size_t i = 0; i < a.vec.size; ++i) {
            if (a.vec.data[i] != b.vec.data[i]) return false;
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const MySet& set) {
        os << "{ ";
        for (size_t i = 0; i < set.vec.size; ++i) {
            os << set.vec.data[i];
            if (i != set.vec.size - 1) os << ", ";
        }
        os << " }";
        return os;
    }
};

template <>
inline void MySet<char*>::sort() {
    std::sort(vec.data, vec.data + vec.size, [](const char* a, const char* b) {
        return strcmp(a, b) < 0;
    });
}

template <>
inline int MySet<char*>::q_find(char* const& element) const {
    int left = 0, right = static_cast<int>(vec.size) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(vec.data[mid], element);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

#endif // MYSET_H

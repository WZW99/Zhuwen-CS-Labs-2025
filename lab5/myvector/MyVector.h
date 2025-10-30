#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>
#include <cstring>
#include <stdexcept>

template <typename T>
class MyVector {
protected:
    struct VectorData {
        size_t size{};
        size_t capacity{8};
        T* data{new T[8]};

        ~VectorData() { delete[] data; }
    } vec;

    void resize() {
        size_t new_capacity = vec.capacity * 2;
        T* new_data = new T[new_capacity];
        std::copy(vec.data, vec.data + vec.size, new_data);
        delete[] vec.data;
        vec.data = new_data;
        vec.capacity = new_capacity;
    }

public:
    MyVector() = default;

    MyVector(const MyVector& other) : vec() {
        while (vec.capacity < other.vec.size) {
            resize();
        }
        std::copy(other.vec.data, other.vec.data + other.vec.size, vec.data);
        vec.size = other.vec.size;
    }

    virtual ~MyVector() = default;

    virtual void add_element(const T& element) {
        if (vec.size >= vec.capacity) resize();
        vec.data[vec.size++] = element;
    }

    virtual void delete_element(size_t index) {
        if (index >= vec.size) return;
        for (size_t i = index; i < vec.size - 1; ++i) {
            vec.data[i] = vec.data[i + 1];
        }
        vec.size--;
    }

    virtual int find(const T& element) const {
        for (size_t i = 0; i < vec.size; ++i) {
            if (vec.data[i] == element) return static_cast<int>(i);
        }
        return -1;
    }

    T& operator[](size_t index) {
        if (index >= vec.size) throw std::out_of_range("Index out of range");
        return vec.data[index];
    }

    // const T& operator[](size_t index) const {
    //     if (index >= vec.size) throw std::out_of_range("Index out of range");
    //     return vec.data[index];
    // }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            while (vec.capacity < other.vec.size) {
                resize();
            }
            std::copy(other.vec.data, other.vec.data + other.vec.size, vec.data);
            vec.size = other.vec.size;
        }
        return *this;
    }

    size_t get_size() const { return vec.size; }
    size_t get_capacity() const { return vec.capacity; }
};

template <>
inline void MyVector<char*>::add_element(char* const& element) {
    if (vec.size >= vec.capacity) resize();
    vec.data[vec.size] = new char[strlen(element) + 1];
    strcpy(vec.data[vec.size], element);
    vec.size++;
}

template <>
inline void MyVector<char*>::delete_element(size_t index) {
    if (index >= vec.size) return;
    delete[] vec.data[index];
    for (size_t i = index; i < vec.size - 1; ++i) {
        vec.data[i] = vec.data[i + 1];
    }
    vec.size--;
}

template <>
inline int MyVector<char*>::find(char* const& element) const {
    for (size_t i = 0; i < vec.size; ++i) {
        if (strcmp(vec.data[i], element) == 0) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

#endif // MYVECTOR_H

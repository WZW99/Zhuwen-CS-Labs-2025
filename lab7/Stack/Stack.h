#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

template<typename TypeName, class Parent>
class ListNode {
private:
    TypeName value;
    ListNode* nextNode = nullptr;

public:
    ListNode(const TypeName& value, ListNode* nextNode = nullptr)
        : value(value), nextNode(nextNode) {}
    ListNode(const ListNode&) = default;
    ~ListNode() = default;
    friend Parent;
};

template<typename TypeName>
class Stack {
private:
    using Node = ListNode<TypeName, Stack<TypeName>>;
    Node* top = nullptr;

    void Copy(const Stack& stack) {
        while (!Empty()) Pop();
        if (stack.Empty()) return;

        Stack temp;
        Node* current = stack.top;
        while (current) {
            temp.Push(current->value);
            current = current->nextNode;
        }
        while (!temp.Empty()) {
            Push(temp.Top());
            temp.Pop();
        }
    }

public:
    Stack() = default;
    Stack(const Stack& stack) { Copy(stack); }

    ~Stack() {
        while (!Empty()) Pop();
    }

    Stack& operator=(const Stack& stack) {
        if (this != &stack) Copy(stack);
        return *this;
    }

    bool Empty() const { return top == nullptr; }

    void Push(const TypeName& value) {
        top = new Node(value, top);
    }

    void Pop() {
        if (Empty()) return;
        Node* temp = top;
        top = top->nextNode;
        delete temp;
    }

    TypeName Top() const {
        if (Empty()) throw std::out_of_range("Stack is empty");
        return top->value;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Stack& stack) {
        Node* current = stack.top;
        while (current) {
            stream << current->value << '\n';
            current = current->nextNode;
        }
        return stream;
    }
};

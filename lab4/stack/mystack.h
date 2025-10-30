#ifndef MYSTACK_H
#define MYSTACK_H

template<class INF, class FRIEND>
class ListNode {
private:
    INF d;
    ListNode* next;
    ListNode() { next = nullptr; }
    friend FRIEND;
};

template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node* top;

public:
    MyStack() : top(nullptr) {}

    ~MyStack() {
        while (!empty()) {
            pop();
        }
    }

    MyStack(const MyStack& other) : top(nullptr) {
        if (!other.empty()) {
            Node* temp = other.top;
            MyStack tempStack;

            while (temp != nullptr) {
                tempStack.push(temp->d);
                temp = temp->next;
            }

            while (!tempStack.empty()) {
                push(tempStack.top_inf());
                tempStack.pop();
            }
        }
    }

    MyStack& operator=(const MyStack& other) {
        if (this != &other) {
            while (!empty()) {
                pop();
            }

            if (!other.empty()) {
                Node* temp = other.top;
                MyStack tempStack;

                while (temp != nullptr) {
                    tempStack.push(temp->d);
                    temp = temp->next;
                }

                while (!tempStack.empty()) {
                    push(tempStack.top_inf());
                    tempStack.pop();
                }
            }
        }
        return *this;
    }

    bool empty() const {
        return top == nullptr;
    }

    bool push(INF n) {
        Node* newNode = new Node();
        newNode->d = n;
        newNode->next = top;
        top = newNode;
        return true;
    }

    bool pop() {
        if (empty()) {
            return false;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    INF top_inf() const {
        return top->d;
    }
};


void Run();

#endif // MYSTACK_H

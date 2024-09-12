#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <ostream>

using std::size_t;

class Node
{
    friend class Stack;
    double data{};
    Node* next{ nullptr };

public:
    Node(double d, Node* n) : data{ d }, next{ n } {}
    Node(const Node& n);
};

class Stack
{
    Node* topPtr{ nullptr };
    size_t size{ 0 };

public:
    Stack(){}
    Stack(const Stack& s);
    ~Stack();

    void push(double data);
    double pop();
    bool empty() const;
    double top() const;

    Stack& operator=(const Stack& s);
};

std::ostream& operator<<(std::ostream& out, Stack& s);

#endif

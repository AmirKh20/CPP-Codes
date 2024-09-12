#include "Stack.h"
#include <ostream>

Node::Node(const Node& n)
{
    this -> data = n.data;
    if(n.next)
        next = new Node(*n.next);
    else
        next = nullptr;
}

Stack::Stack(const Stack& s)
{
    topPtr = new Node(*s.topPtr);
    size = s.size;
}

Stack& Stack::operator=(const Stack& s)
{
    this -> ~Stack();

    topPtr = new Node(*s.topPtr);
    size = s.size;

    return *this;
}

Stack::~Stack()
{
    Node* iterPtr{ topPtr };
    for(size_t i{ 0 }; i < size; i++)
    {
        Node* tmpNode{ iterPtr };
        delete tmpNode;
        iterPtr = iterPtr -> next;
    }
    topPtr = nullptr;
    size = 0;
}

void Stack::push(double data)
{
    Node* newNode{ new Node(data, topPtr) };
    topPtr = newNode;
    size++;
}

double Stack::pop()
{
    if(this->empty())
        throw std::out_of_range("Stack Is Empty. Cannot remove an element!");

    Node* tmpTop{ topPtr };
    double data = topPtr->data;
    topPtr = topPtr->next;
    size--;

    delete tmpTop;
    return data;
}

bool Stack::empty() const
{
    return size == 0;
}

double Stack::top() const
{
    if(!topPtr)
        throw std::out_of_range("Stack Is Empty!");
    return topPtr->data;
}

std::ostream& operator<<(std::ostream& out, Stack& s)
{
    while(!s.empty())
        out << s.pop() << ' ';
    return out;
}

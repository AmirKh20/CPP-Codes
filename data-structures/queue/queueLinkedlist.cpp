#include <iostream>
#include <stdexcept>
#include <cstddef>

using std::size_t;

class Node
{
    friend class Queue;
    int data{};
    Node* next{ nullptr };

public:
    Node(int d, Node* n = nullptr) : data{ d }, next{ n } {}
    Node(const Node& n);
};

Node::Node(const Node& n)
{
    data = n.data;
    if(n.next)
        next = new Node(*n.next);
    else
        next = nullptr;
}

class Queue
{
    Node* frontPtr{ nullptr };
    Node* backPtr{ nullptr };
    size_t size{ 0 };

public:
    Queue(){}
    Queue(const Queue& q);
    ~Queue();

    void push(int data);
    int pop();
    bool empty() const;
    int front() const;
    int back() const;
    size_t getSize() const;

    Queue& operator=(const Queue& q);
};

Queue::Queue(const Queue& q)
{
    if(q.empty())
        return;
    frontPtr = new Node(*q.frontPtr);

    Node* iterPtr{ frontPtr };
    while(iterPtr -> next != nullptr)
        iterPtr = iterPtr -> next;
    backPtr = iterPtr;

    size = q.size;
}

Queue& Queue::operator=(const Queue& q)
{
    this -> ~Queue();
    if(q.empty())
        return *this;

    frontPtr = new Node(*q.frontPtr);

    Node* iterPtr{ frontPtr };
    while(iterPtr -> next != nullptr)
        iterPtr = iterPtr -> next;
    backPtr = iterPtr;

    size = q.size;
    return *this;
}

Queue::~Queue()
{
    while(!empty())
        pop();
}

bool Queue::empty() const
{
    return(!frontPtr && !backPtr);
}

void Queue::push(int data)
{
    Node* newNode{ new Node(data) };
    if(empty())
    {
        frontPtr = newNode;
        backPtr = newNode;
        return;
    }

    backPtr -> next = newNode;
    backPtr = newNode;
    size++;
}

int Queue::pop()
{
    if(empty())
        throw std::underflow_error("Queue is empty. Cannot remove anything!");

    Node* tmpFront{ frontPtr };
    int frontData{ frontPtr -> data };

    frontPtr = frontPtr -> next;

    if(frontPtr == nullptr)
        backPtr = nullptr;

    size--;
    delete tmpFront;
    return frontData;
}

int Queue::front() const
{
    if(!frontPtr)
        throw std::out_of_range("Queue is empty. There is no Front Element!");
    return frontPtr -> data;
}

int Queue::back() const
{
    if(!backPtr)
        throw std::out_of_range("Queue is empty. There is no Back Element!");
    return backPtr -> data;
}

size_t Queue::getSize() const
{
    return size;
}

std::ostream& operator<<(std::ostream& out, Queue& q)
{
    while(!q.empty())
        out << q.pop() << ' ';
    return out;
}

int main()
{
    Queue q;
    q.push(1);
    q.push(2);
    std::cout << q.front() << ' ';
    std::cout << q.back() << '\n';
    q.push(3);
    std::cout << q.front() << ' ';
    std::cout << q.back() << '\n';
    q.pop();

    Queue q2(q);
    std::cout << q << '\n';
    std::cout << q2 << '\n';

    q2 = q;
    std::cout << q << '\n';
    std::cout << q2 << '\n';
    return 0;
}

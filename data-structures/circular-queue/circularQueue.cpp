#include <iostream>

using std::size_t;

class Queue{
    double* arr{ nullptr };
    double* frontPtr{ nullptr };
    double* backPtr{ nullptr };
    size_t maxSize{ 0 };

    double* addOneToPtr(double* ptr) const;

public:
    Queue(size_t s);
    Queue(const Queue& q);
    Queue& operator= (const Queue& q);
    ~Queue();
    void push(double newElement);
    double pop();
    double front() const;
    double back() const;
    bool empty() const;
    bool full() const;

    friend std::ostream& operator<< (std::ostream& out, Queue& q);
};

Queue::Queue(size_t s)
{
    arr = new double[s]{};
    maxSize = s;
}

Queue::Queue(const Queue& q)
{
    if(q.empty())
        return;

    maxSize = q.maxSize;
    arr = new double[maxSize]{};

    for(size_t i{ 0 }; i < maxSize; i++)
        arr[i] = q.arr[i];

    size_t frontIndex = q.frontPtr - q.arr;
    size_t backIndex = q.backPtr - q.arr;

    frontPtr = arr + frontIndex;
    backPtr = arr + backIndex;
}

Queue& Queue::operator= (const Queue& q)
{
    if(q.empty())
        return *this;

    this->~Queue();

    maxSize = q.maxSize;
    arr = new double[maxSize]{};

    for(size_t i{ 0 }; i < maxSize; i++)
        arr[i] = q.arr[i];

    size_t frontIndex = q.frontPtr - q.arr;
    size_t backIndex = q.backPtr - q.arr;

    frontPtr = arr + frontIndex;
    backPtr = arr + backIndex;

    return *this;
}

Queue::~Queue()
{
    delete[] arr;
    frontPtr = backPtr = nullptr;
    maxSize = 0;
}

double* Queue::addOneToPtr(double* ptr) const
{
    if(ptr == arr+maxSize-1)
        ptr = arr;
    else
        ptr += 1;
    return ptr;
}

bool Queue::full() const
{
    if(addOneToPtr(backPtr) == frontPtr)
        return true;
    return false;
}

void Queue::push(double newElement)
{
    if(this->full())
        throw std::out_of_range("The Queue is Full");

    if(backPtr && frontPtr)
        backPtr = addOneToPtr(backPtr);
    else
    {
        backPtr = arr;
        frontPtr = arr;
    }

    *backPtr = newElement;
}

double Queue::pop()
{
    if(this->empty())
        throw std::out_of_range("The Queue is Empty");

    double* firstElement{ frontPtr };
    if(frontPtr == backPtr)
        frontPtr = backPtr = nullptr;
    else
        frontPtr = addOneToPtr(frontPtr);
    return *firstElement;
}

double Queue::front() const
{
    if(this->empty())
        throw std::out_of_range("The Queue is Empty");
    return *frontPtr;
}

double Queue::back() const
{
    if(this->empty())
        throw std::out_of_range("The Queue is Empty");
    return *backPtr;
}

bool Queue::empty() const
{
    if(!frontPtr && !backPtr)
        return true;

    return false;
}

std::ostream& operator<< (std::ostream& out, Queue& q)
{
    while(!q.empty())
        out << q.pop() << ' ';
    return out;
}

int main()
{
    Queue q(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    std::cout << q.front() << ' ' << q.back() << '\n';
    q.pop();
    std::cout << q.front() << ' ' << q.back() << '\n';

    Queue q2(q);
    std::cout << q << '\n';

    std::cout << q2.front() << ' ' << q2.back() << '\n';
    q2.push(6);
    std::cout << q2.front() << ' ' << q2.back() << '\n';
    std::cout << q2 << '\n';

    q = q2;
    std::cout << q << '\n';

    return 0;
}

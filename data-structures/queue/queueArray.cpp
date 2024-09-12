#include <iostream>

using std::size_t;

class Queue
{
    double* arr{ nullptr };
    size_t size{ 0 };

public:
    Queue(){}
    Queue(const std::initializer_list<double>& il);
    Queue(const Queue& q);
    Queue& operator =(const Queue& q);
    ~Queue();
    size_t push(double element);
    double pop();
    double front() const;
    double back() const;
    bool empty() const;
    size_t getSize() const;
    friend std::ostream& operator <<(std::ostream& out, Queue& q);
    friend std::istream& operator >>(std::istream& in, Queue& q);
};

Queue::Queue(const std::initializer_list<double>& il)
{
    for(auto el : il)
        this->push(el);
}

Queue::Queue(const Queue& s)
{
    arr = new double[s.size]{};
    size = s.size;
    for(size_t i{ 0 }; i < size; i++)
        arr[i] = s.arr[i];
}

Queue& Queue::operator =(const Queue& s)
{
    delete[] arr;
    arr = new double[s.size]{};
    size = s.size;

    for(size_t i{ 0 }; i < size; i++)
        arr[i] = s.arr[i];
    return *this;
}

Queue::~Queue()
{
    delete[] arr;
    size = 0;
}

size_t Queue::push(double element)
{
    Queue tmp(*this);

    delete[] arr;
    arr = new double[size+1]{};
    for(size_t i{ 0 }; i < size; i++)
        arr[i] = tmp.arr[i];

    arr[size] = element;
    size++;
    return size;
}

double Queue::pop()
{
    if(this->empty())
        throw std::out_of_range("There is no elements in the queue");

    double* copyArr{ new double[size-1]{} };
    for(size_t i{ 1 }; i < size; i++)
        copyArr[i-1] = arr[i];

    double firstElement{ arr[0] };
    delete[] arr;
    arr = copyArr;
    size--;
    return firstElement;
}

double Queue::front() const
{
    if(this->empty())
        throw std::out_of_range("There is no elements in the queue");
    return arr[0];
}

double Queue::back() const
{
    if(this->empty())
        throw std::out_of_range("There is no elements in the queue");
    return arr[size-1];
}

bool Queue::empty() const
{
    return (size == 0);
}

size_t Queue::getSize() const
{
    return size;
}

std::ostream& operator <<(std::ostream& out, Queue& s)
{
    while(!s.empty())
        out << s.pop() << ' ';
    return out;
}

std::istream& operator >>(std::istream& in, Queue& s)
{
    size_t numberOfNewElements{};
    std::cout << "How many number: ";
    in >> numberOfNewElements;

    for(size_t i{ 1 }; i <= numberOfNewElements; i++)
    {
        double newElement{};
        in >> newElement;
        s.push(newElement);
    }
    return in;
}

int main()
{
    Queue q1({1, 2});
    q1.push(3);
    q1.push(4);
    std::cout << "q1: " << q1 << '\n';
    std::cin >> q1;
    std::cout << "back = " << q1.back() << '\n';
    std::cout << "front = " << q1.front() << '\n';
    std::cout << "size = " << q1.getSize() << '\n';
    return 0;
}

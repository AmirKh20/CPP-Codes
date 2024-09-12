#include <iostream>

using std::size_t;

class Stack
{
    double* arr{ nullptr };
    size_t size{ 0 };

public:
    Stack(){}
    Stack(const std::initializer_list<double>& il);
    Stack(const Stack& s);
    Stack& operator =(const Stack& s);
    ~Stack();
    size_t push(double element);
    double pop();
    double top() const;
    bool empty() const;
    size_t getSize() const;
    friend std::ostream& operator <<(std::ostream& out, Stack& s);
    friend std::istream& operator >>(std::istream& in, Stack& s);
};

Stack::Stack(const std::initializer_list<double>& il)
{
    for(auto el : il)
        this->push(el);
}

Stack::Stack(const Stack& s)
{
    arr = new double[s.size]{};
    size = s.size;
    for(size_t i{ 0 }; i < size; i++)
        arr[i] = s.arr[i];
}

Stack& Stack::operator =(const Stack& s)
{
    delete[] arr;
    arr = new double[s.size]{};
    size = s.size;

    for(size_t i{ 0 }; i < size; i++)
        arr[i] = s.arr[i];
    return *this;
}

Stack::~Stack()
{
    delete[] arr;
    size = 0;
}

size_t Stack::push(double element)
{
    Stack tmp(*this);

    delete[] arr;
    arr = new double[size+1]{};
    for(size_t i{ 0 }; i < size; i++)
        arr[i] = tmp.arr[i];

    arr[size] = element;
    size++;
    return size;
}

double Stack::pop()
{
    if(this->empty())
        throw std::out_of_range("There is no elements in the stack");

    double* copyArr{ new double[size-1]{} };
    for(size_t i{ 0 }; i < size-1; i++)
        copyArr[i] = arr[i];

    double lastElement{ arr[size-1] };
    delete[] arr;
    arr = copyArr;
    size--;
    return lastElement;
}

double Stack::top() const
{
    return arr[size-1];
}

bool Stack::empty() const
{
    return (size == 0);
}

size_t Stack::getSize() const
{
    return size;
}

std::ostream& operator <<(std::ostream& out, Stack& s)
{
    while(!s.empty())
        out << s.pop() << ' ';
    return out;
}

std::istream& operator >>(std::istream& in, Stack& s)
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
    Stack s1({1, 2});
    s1.push(3);
    s1.push(4);
    std::cout << "s1: " << s1 << '\n';
    std::cin >> s1;
    std::cout << "top = " << s1.top() << '\n';
    std::cout << "size = " << s1.getSize() << '\n';
    return 0;
}

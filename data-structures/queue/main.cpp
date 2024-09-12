#include <iostream>
#include <vector>

using std::size_t;

class Queue
{
    double* arr{ new double[]}
    std::vector<double> vec;
    size_t size{ 0 };
    double* front{ nullptr };
    double* back{ nullptr };

public:
    Queue() {}
    void push(double newElement);
};

void push(double newElement)
{
    vec.push_back(newElement);
    if(back) back++;
    else back = vec.begin();
}

int main()
{
    return 0;
}

#include <iostream>
#include <cmath>

using std::size_t;

class Polymonial
{
    double* arr{ nullptr };
    size_t size{ 0 };

public:
    Polymonial(size_t maximumPower);
    Polymonial(const Polymonial& p);
    friend std::istream& operator >>(std::istream& in, Polymonial& p);
    friend std::ostream& operator <<(std::ostream& out, const Polymonial& p);
    friend Polymonial operator +(const Polymonial& p1, const Polymonial& p2);
    Polymonial operator -() const;
    friend Polymonial operator -(const Polymonial& p1, const Polymonial& p2);
    friend Polymonial operator *(const Polymonial& p1, const Polymonial& p2);
    double calculate(double x) const;
};

Polymonial::Polymonial(size_t maximumPower)
{
    arr = new double[maximumPower+1]{};
    size = maximumPower+1;
}

Polymonial::Polymonial(const Polymonial& p)
{
    this->arr = new double[p.size]{};
    this->size = p.size;
    for(size_t i = 0; i < p.size; i++)
        this->arr[i] = p.arr[i];
}

std::istream& operator >>(std::istream& in, Polymonial& p)
{
    if(p.size == 0)
    {
        std::cerr << "Error: Define a size first" << '\n';
        return in;
    }
    std::cout << "Enter The Coefficent of Power ";
    for(size_t i = 0; i < p.size; i++)
    {
        std::cout << "#" << i << ": ";
        in >> p.arr[i];
    }
    return in;
}

std::ostream& operator <<(std::ostream& out, const Polymonial& p)
{
    if(p.size == 0)
    {
        std::cerr << "Empty!" << '\n';
        return out;
    }
    for(size_t i = 0; i < p.size; i++)
    {
        if(p.arr[i] != 0)
        {
            if(p.arr[i] > 0)
                out << '+';
            out << p.arr[i];
            if(i != 0)
                out << "x^" << i;
        }
    }
    return out;
}

Polymonial operator +(const Polymonial& p1, const Polymonial& p2)
{
    size_t p3_maximumPower = ((p1.size > p2.size) ? p1.size : p2.size) - 1;
    Polymonial p3(p3_maximumPower);
    for(size_t i = 0; i < p3.size; i++)
    {
        if(i >= p1.size)
            p3.arr[i] = p2.arr[i];
        else if(i >= p2.size)
            p3.arr[i] = p1.arr[i];
        else
            p3.arr[i] = p1.arr[i] + p2.arr[i];
    }
    return p3;
}

Polymonial Polymonial::operator -() const
{
    Polymonial negetiveP(*this);
    for(size_t i = 0; i < size; i++)
        negetiveP.arr[i] = -negetiveP.arr[i];
    return negetiveP;
}

Polymonial operator -(const Polymonial& p1, const Polymonial& p2)
{
    return(p1 + (-p2));
}

Polymonial operator *(const Polymonial& p1, const Polymonial& p2)
{
    Polymonial p3(p1.size + p2.size - 2);
    for(size_t i = 0; i < p1.size; i++)
    {
        if(p1.arr[i] == 0)
            continue;
        for(size_t j = 0; j < p2.size; j++)
        {
            if(p2.arr[j] == 0)
                continue;
            p3.arr[i+j] += p1.arr[i] * p2.arr[j];
        }
    }
    return p3;
}

double Polymonial::calculate(double x) const
{
    double result{ 0.0 };
    for(size_t i{ 0 }; i < size; i++)
        result += arr[i] * std::pow(x, i);
    return result;
}

int main()
{
    size_t p1MaxPower{};
    std::cout << "Enter the maximum Power of first Polymonial: ";
    std::cin >> p1MaxPower;

    Polymonial p1(p1MaxPower);
    std::cin >> p1;
    std::cout << "p1 = " << p1 << '\n';

    size_t p2MaxPower{};
    std::cout << "Enter the maximum power of second Polymonial: ";
    std::cin >> p2MaxPower;

    Polymonial p2(p2MaxPower);
    std::cin >> p2;
    std::cout << "p2 = " << p2 << '\n';

    std::cout << "p1 + p2 = ";
    std::cout << (p1 + p2) << '\n';

    std::cout << "p1 - p2 = ";
    std::cout << (p1 - p2) << '\n';

    std::cout << "p1 * p2 = ";
    std::cout << (p1 * p2) << '\n';

    int x{};
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << p1.calculate(x) << '\n';
    return 0;
}

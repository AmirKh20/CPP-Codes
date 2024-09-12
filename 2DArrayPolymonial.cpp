#include <iostream>
#include <algorithm>
#include <cmath>

using std::size_t;

class Polymonial
{
    double** arr{ nullptr };
    size_t size{ 0 };

public:
    Polymonial(size_t s);
    Polymonial(const Polymonial& p);
    friend std::istream& operator >>(std::istream& in, Polymonial& p);
    friend std::ostream& operator <<(std::ostream& out, const Polymonial& p);
    friend Polymonial operator +(const Polymonial& p1, const Polymonial& p2);
    Polymonial operator -() const;
    friend Polymonial operator -(const Polymonial& p1, const Polymonial& p2);
    friend Polymonial operator *(const Polymonial& p1, const Polymonial& p2);
    double calculate(double x) const;
    void simplify();
};

Polymonial::Polymonial(size_t s)
{
    arr = new double*[s];
    for(size_t i{ 0 }; i < s; i++)
        arr[i] = new double[2]{};
    size = s;
}

Polymonial::Polymonial(const Polymonial& p)
{
    arr = new double*[p.size];
    for(size_t i{ 0 }; i < p.size; i++)
        arr[i] = new double[2]{ p.arr[i][0], p.arr[i][1] };
    size = p.size;
}

bool sortPowers(double* a, double* b)
{
    return(a[0] <= b[0]);
}

std::istream& operator >>(std::istream& in, Polymonial& p)
{
    if(p.size == 0)
    {
        std::cerr << "Error: Enter the size first!" << '\n';
        return in;
    }
    for(size_t i{ 0 }; i < p.size; i++)
    {
        std::cout << "Power #" << i+1 << ": ";
        in >> p.arr[i][0];
        std::cout << "Coefficient #" << i+1 << ": ";
        in >> p.arr[i][1];
    }
    std::sort(p.arr, p.arr+p.size, sortPowers);
    return in;
}

std::ostream& operator <<(std::ostream& out, const Polymonial& p)
{
    if(p.size == 0)
        out << "Empty!" << '\n';

    for(size_t i{ 0 }; i < p.size; i++)
    {
        if(p.arr[i][1] != 0)
        {
            if(p.arr[i][1] > 0)
                out << '+';
            out << p.arr[i][1];
            if(p.arr[i][0] != 0)
                out << "x^" << p.arr[i][0];
        }
    }
    return out;
}

Polymonial operator +(const Polymonial& p1, const Polymonial& p2)
{
    Polymonial p3(p1.size + p2.size);

    size_t i1{ 0 };
    size_t i2{ 0 };
    size_t i3{ 0 };
    while(i1 < p1.size && i2 < p2.size)
    {
        if(p1.arr[i1][0] < p2.arr[i2][0])
        {
            p3.arr[i3][0] = p1.arr[i1][0];
            p3.arr[i3][1] = p1.arr[i1][1];
            i1++;
            i3++;
        }
        else if(p2.arr[i2][0] < p1.arr[i1][0])
        {
            p3.arr[i3][0] = p2.arr[i2][0];
            p3.arr[i3][1] = p2.arr[i2][1];
            i2++;
            i3++;
        }
        else
        {
            p3.arr[i3][0] = p1.arr[i1][0];
            p3.arr[i3][1] = p1.arr[i1][1] + p2.arr[i2][1];
            i1++;
            i2++;
            i3++;
        }
    }
    while(i1 < p1.size)
    {
        p3.arr[i3][0] = p1.arr[i1][0];
        p3.arr[i3][1] = p1.arr[i1][1];
        i1++;
        i3++;
    }
    while(i2 < p2.size)
    {
        p3.arr[i3][0] = p2.arr[i2][0];
        p3.arr[i3][1] = p2.arr[i2][1];
        i2++;
        i3++;
    }
    return p3;
}

Polymonial Polymonial::operator -() const
{
    Polymonial negetiveP(*this);

    for(size_t i{ 0 }; i < size; i++)
        negetiveP.arr[i][1] = -negetiveP.arr[i][1];

    return negetiveP;
}

Polymonial operator -(const Polymonial& p1, const Polymonial& p2)
{
    return(p1 + (-p2));
}

Polymonial operator *(const Polymonial& p1, const Polymonial& p2)
{
    Polymonial p3(p1.size * p2.size);
    size_t k{ 0 };
    for(size_t i{ 0 }; i < p1.size; i++)
    {
        if(p1.arr[i][1] == 0)
            continue;
        for(size_t j{ 0 }; j < p2.size; j++)
        {
            if(p2.arr[j][1] == 0)
                continue;
            p3.arr[k][0] = p1.arr[i][0] + p2.arr[j][0];
            p3.arr[k][1] = p1.arr[i][1] * p2.arr[j][1];
            k++;
        }
    }
    return p3;;
}

double Polymonial::calculate(double x) const
{
    double result{ 0.0 };
    for(size_t i{ 0 }; i < size; i++)
        result += arr[i][1] * std::pow(x, arr[i][0]);
    return result;
}

void Polymonial::simplify()
{
    for(size_t i{ 0 }; i < size; i++)
        for(size_t j{ i+1 }; j < size; j++)
            if(arr[i][0] == arr[j][0])
            {
                arr[i][1] += arr[j][1];
                arr[j][1] = 0;
            }
}

int main()
{
    size_t p1Size{};
    std::cout << "Enter the size of first Polymonial: ";
    std::cin >> p1Size;

    Polymonial p1(p1Size);
    std::cin >> p1;
    std::cout << "p1 = " << p1 << '\n';

    size_t p2Size{};
    std::cout << "Enter the size of second Polymonial: ";
    std::cin >> p2Size;

    Polymonial p2(p2Size);
    std::cin >> p2;
    std::cout << "p2 = " << p2 << '\n';

    std::cout << "p1 + p2 = ";
    std::cout << (p1 + p2) << '\n';

    std::cout << "p1 - p2 = ";
    std::cout << (p1 - p2) << '\n';

    std::cout << "p1 * p2 = ";
    Polymonial p3(p1 * p2);
    p3.simplify();
    std::cout << p3 << '\n';

    int x{};
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << p1.calculate(x) << '\n';
    return 0;
}

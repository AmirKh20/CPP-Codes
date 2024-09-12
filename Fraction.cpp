#include <iostream>
#include <numeric> //std::gcd and std::lcm

class Fraction
{
    int numerator{};
    int denominator{ 1 };

    public:
    Fraction(){}
    Fraction(int num, int den = 1);
    Fraction(const Fraction& f);

    Fraction& operator= (const Fraction& f);
    friend std::ostream& operator<< (std::ostream& out, const Fraction& f);
    friend std::istream& operator>> (std::istream& in, Fraction& f);
    Fraction operator+ (const Fraction& f2) const;
    Fraction operator- (const Fraction& f2) const;
    Fraction operator* (const Fraction& f2) const;
    Fraction operator/ (const Fraction& f2) const;
    Fraction& operator+= (const Fraction& f2);
    Fraction& operator-= (const Fraction& f2);
    Fraction& operator*= (const Fraction& f2);
    Fraction& operator/= (const Fraction& f2);
    bool operator== (const Fraction& f2) const;
    bool operator!= (const Fraction& f2) const;
    bool operator< (const Fraction& f2) const;
    bool operator<= (const Fraction& f2) const;
    bool operator> (const Fraction& f2) const;
    bool operator>= (const Fraction& f2) const;
};

Fraction::Fraction(int num, int den)
{
    numerator = ((num >= 0) ? num : 0);
    denominator = ((den != 0) ? den : 1);

    int gcdValue{ std::gcd(numerator, denominator) };
    numerator /= gcdValue;
    if(numerator != 0)
        denominator /= gcdValue;
}

Fraction::Fraction(const Fraction& f)
{
    numerator = f.numerator;
    denominator = f.denominator;
}

Fraction& Fraction::operator= (const Fraction& f)
{
    numerator = f.numerator;
    denominator = f.denominator;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Fraction& f)
{
    out << f.numerator << '/' << f.denominator <<
        " = " << static_cast<double>(f.numerator)/f.denominator << '\n';
    return out;
}

std::istream& operator>> (std::istream& in, Fraction& f)
{
    in >> f.numerator;
    in.ignore(100, '/');
    in >> f.denominator;
    return in;
}

Fraction Fraction::operator+ (const Fraction& f2) const
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    Fraction f3(firstNumerator + secondNumerator, lcmValue);
    return f3;
}

Fraction& Fraction::operator+= (const Fraction& f2)
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };

    *this = Fraction(firstNumerator + secondNumerator, lcmValue);
    return *this;
}

Fraction Fraction::operator- (const Fraction& f2) const
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    Fraction f3(firstNumerator - secondNumerator, lcmValue);
    return f3;
}

Fraction& Fraction::operator-= (const Fraction& f2)
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    *this = Fraction(firstNumerator - secondNumerator, lcmValue);
    return *this;
}

Fraction Fraction::operator* (const Fraction& f2) const
{
    Fraction f3(numerator * f2.numerator, denominator * f2.denominator);
    return f3;
}

Fraction& Fraction::operator*= (const Fraction& f2)
{
    *this = Fraction(numerator * f2.numerator, denominator * f2.denominator);
    return *this;
}

Fraction Fraction::operator/ (const Fraction& f2) const
{
    Fraction f3(*this * Fraction(f2.denominator, f2.numerator));
    return f3;
}

Fraction& Fraction::operator/= (const Fraction& f2)
{
    *this = Fraction(*this * Fraction(f2.denominator, f2.numerator));
    return *this;
}

bool Fraction::operator== (const Fraction& f2) const
{
    return((numerator == f2.numerator) && (denominator == f2.denominator));
}

bool Fraction::operator!= (const Fraction& f2) const
{
    return((numerator != f2.numerator) || (denominator != f2.denominator));
}

bool Fraction::operator< (const Fraction& f2) const
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    return(firstNumerator < secondNumerator);
}

bool Fraction::operator<= (const Fraction& f2) const
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    return(firstNumerator <= secondNumerator);
}

bool Fraction::operator> (const Fraction& f2) const
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    return(firstNumerator > secondNumerator);
}

bool Fraction::operator>= (const Fraction& f2) const
{
    int lcmValue{ std::lcm(denominator, f2.denominator) };
    int firstNumerator{ (lcmValue / denominator) * numerator };
    int secondNumerator{ (lcmValue / f2.denominator) * f2.numerator };
    return(firstNumerator >= secondNumerator);
}

int main()
{
    Fraction f1(2 ,5);
    Fraction f2(2, 8);
    Fraction f3(f1 / f2);
    std::cout << f3;

    Fraction f4;
    std::cin >> f4;
    Fraction f5;
    std::cin >> f5;

    std::cout << "f4 + f5 = " << (f4 + f5);
    std::cout << "f4 - f5 = " << (f4 - f5);
    std::cout << "f4 * f5 = " << (f4 * f5);
    std::cout << "f4 / f5 = " << (f4 / f5);

    std::cout << "f4 += f5 = " << (f4 += f5);
    std::cout << "f4 -= f5 = " << (f4 -= f5);
    std::cout << "f4 *= f5 = " << (f4 *= f5);
    std::cout << "f4 /= f5 = " << (f4 /= f5);

    std::cout << std::boolalpha;
    std::cout << "f4 == f5: " << (f4 == f5) << '\n';
    std::cout << "f4 != f5: " << (f4 != f5) << '\n';
    std::cout << "f4 < f5: " << (f4 < f5) << '\n';
    std::cout << "f4 <= f5: " << (f4 <= f5) << '\n';
    std::cout << "f4 > f5: " << (f4 > f5) << '\n';
    std::cout << "f4 >= f5: " << (f4 >= f5) << '\n';

    return 0;
}

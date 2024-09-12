#include <map>
#include <iostream>
#ifndef MONOMIAL_H
#define MONOMIAL_H
class Polynomial;

class Monomial
{
    using map = std::map<char, int>;
    friend class Polynomial;
    friend Polynomial operator+ (const Polynomial& p1, const Polynomial& p2);

    private:
    double coefficient{ 1.0 };
    map variables_exponents{};

    public:
    Monomial(){}
    Monomial(double coefficient, char variable = 0, int exponent = 1);
    Monomial(double coefficient, int exponent);
    Monomial(double coefficient, const map& vars);
    Monomial(char variable, int exponent);
    Monomial(char variable);
    Monomial(const map& vars);
    Monomial(const Monomial& m);
    double getCoefficient() const { return coefficient; }
    Monomial& operator= (const Monomial& m);
    friend std::ostream& operator<< (std::ostream& out, const Monomial& m);
    friend std::istream& operator>> (std::istream& in, Monomial& m);
    Monomial operator+ (const Monomial& m2) const;
    Monomial operator- (const Monomial& m2) const;
    Monomial operator* (const Monomial& m2) const;
    Monomial& operator+= (const Monomial& m2);
    bool operator== (const Monomial& m2) const;
    bool operator!= (const Monomial& m2) const;
};

bool isAlpha(char ch);

#endif

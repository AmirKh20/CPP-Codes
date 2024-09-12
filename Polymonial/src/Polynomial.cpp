#include "Monomial.h"
#include "Polynomial.h"
#include <vector>
#include <iostream>
#include <map>
using vector = std::vector<Monomial>;
using size_t = std::vector<Monomial>::size_type;
using iterator = std::vector<Monomial>::iterator;
using const_iterator = std::vector<Monomial>::const_iterator;
using map = std::map<char, int>;

Polynomial::Polynomial(const vector& monomials, size_t len)
{
    Polynomial simplifiedPolynomial;
    std::vector<bool> visited(monomials.size(), false);
    for(size_t i{ 0 }; i < monomials.size()-1; i++)
    {
        if(visited.at(i))
            continue;
        Monomial sum{ monomials.at(i) };
        for(size_t j{ i + 1 }; j < monomials.size(); j++)
            if(monomials[i].variables_exponents == monomials[j].variables_exponents)
            {
                sum += monomials[j];
                visited.at(j) = true;
            }
        simplifiedPolynomial.monomials.push_back(sum);
    }
    if(!visited.back())
        simplifiedPolynomial.monomials.push_back(monomials.back());

    if(len == npos)
        *this = simplifiedPolynomial;
    else
        this->monomials.assign(simplifiedPolynomial.begin(), simplifiedPolynomial.begin() + len);
}

Polynomial::Polynomial(const Polynomial& p)
{
    *this = Polynomial(p.monomials);
}

Polynomial& Polynomial::operator= (const Polynomial& p)
{
    monomials = p.monomials;
    return *this;
}

bool Polynomial::contains(const map& variables_exponents) const
{
    for(auto it{ begin() }; it != end(); ++it)
        if(it->variables_exponents == variables_exponents)
            return true;
    return false;
}

bool Polynomial::contains(const Monomial& m) const
{
    for(auto it{ begin() }; it != end(); ++it)
        if(*it == m)
            return true;
    return false;
}

bool Polynomial::isEmpty() const
{
    return monomials.empty();
}

size_t Polynomial::getSize() const
{
    return monomials.size();
}

void Polynomial::resize(size_t s)
{
    monomials.resize(s);
}

iterator Polynomial::begin()
{
    return (monomials.begin());
}

const_iterator Polynomial::begin() const
{
    return (monomials.begin());
}

iterator Polynomial::end()
{
    return (monomials.end());
}

const_iterator Polynomial::end() const
{
    return (monomials.end());
}

Monomial& Polynomial::operator[](size_t pos)
{
    return (monomials.at(pos));
}

Monomial Polynomial::operator[](size_t pos) const
{
    return (monomials.at(pos));
}

Polynomial Polynomial::operator-() const
{
    Polynomial p2(*this);
    for(auto& el : p2.monomials)
        el.coefficient = -el.coefficient;
    return p2;
}

Polynomial& Polynomial::operator+= (const Monomial& m)
{
    this->push_back(m);
    return *this;
}

void Polynomial::push_back(const Monomial& m)
{
    monomials.push_back(m);
    *this = Polynomial(this->monomials);
}

Polynomial operator+ (const Polynomial& p1, const Polynomial& p2)
{
    Polynomial p3;
    for(auto it1{ p1.begin() }; it1 != p1.end(); ++it1)
    {
        Monomial sum{ *it1 };
        for(auto it2{ p2.begin() }; it2 != p2.end(); ++it2)
            if(it1->variables_exponents == it2->variables_exponents)
            {
                sum += *it2;
                break;
            }
        p3 += sum;
    }
    for(auto it2{ p2.begin() }; it2 != p2.end(); ++it2)
        if(!p1.contains(it2->variables_exponents))
            p3 += *it2;

    return p3;
}

Polynomial& Polynomial::operator+= (const Polynomial& p)
{
    *this = *this + p;
    return *this;
}

Polynomial operator- (const Polynomial& p1, const Polynomial& p2)
{
    return (p1 + (-p2));
}

Polynomial& Polynomial::operator-= (const Polynomial& p)
{
    *this = *this - p;
    return *this;
}

Polynomial operator* (const Polynomial& p1, const Polynomial& p2)
{
    Polynomial p3;
    for(auto it1{ p1.begin() }; it1 != p1.end(); ++it1)
        for(auto it2{ p2.begin() }; it2 != p2.end(); ++it2)
            p3 += (*it1)*(*it2);
    return p3;
}

bool operator== (const Polynomial& p1, const Polynomial& p2)
{
    if(p1.getSize() != p2.getSize())
        return false;
    for(size_t i{ 0 }; i < p1.getSize(); i++)
        if(!p2.contains(p1[i]))
            return false;
    return true;
}

std::ostream& operator<< (std::ostream& out, const Polynomial& p)
{
    for(auto& el : p)
    {
        if(el.getCoefficient() > 0)
            out << '+';
        out << el << ' ';
    }
    return out;
}

std::istream& operator>> (std::istream& in, Polynomial& p)
{
    if(p.getSize() == 0)
    {
        std::cout << "Enter the size of the polynomial: ";
        size_t s;
        in >> s;
        p.resize(s);
    }
    for(auto& el : p)
        in >> el;
    return in;
}

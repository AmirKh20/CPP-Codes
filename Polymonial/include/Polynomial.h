#include "Monomial.h"
#include <vector>
#include <iostream>
#include <map>
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial
{
    using vector = std::vector<Monomial>;
    using size_t = std::vector<Monomial>::size_type;
    using iterator = std::vector<Monomial>::iterator;
    using const_iterator = std::vector<Monomial>::const_iterator;
    using map = std::map<char, int>;

    friend Polynomial operator+ (const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator- (const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator* (const Polynomial& p1, const Polynomial& p2);
    friend bool operator== (const Polynomial& p1, const Polynomial& p2);
    friend std::ostream& operator<< (std::ostream& out, const Polynomial& p);
    friend std::istream& operator>> (std::istream& in, Polynomial& p);

    private:
    vector monomials{};

    public:
    static const size_t npos{ static_cast<size_t>(-1) };
    Polynomial(){}
    Polynomial(const vector& monomials, size_t len = npos);
    Polynomial(const Polynomial& p);
    Polynomial& operator= (const Polynomial& p);

    bool isEmpty() const;
    size_t getSize() const;
    void resize(size_t s);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    Monomial& operator[](size_t pos);
    Monomial operator[](size_t pos) const;
    Polynomial operator-() const;
    bool contains(const map& variables_exponents) const;
    bool contains(const Monomial& m) const;
    Polynomial& operator+= (const Monomial& m);
    void push_back(const Monomial& m);
    Polynomial& operator+= (const Polynomial& p);
    Polynomial& operator-= (const Polynomial& p);
};
#endif

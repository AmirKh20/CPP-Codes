#include "Monomial.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using map = std::map<char, int>;

bool isAlpha(char ch)
{
    return((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

Monomial::Monomial(double coefficient, char variable, int exponent)
{
    this->coefficient = ((coefficient != 0.0) ? coefficient : 1.0);
    variable = (isAlpha(variable) ? variable : 0);
    exponent = ((exponent >= 0) ? exponent : 1);
    if(variable != 0 && exponent != 0)
        variables_exponents[variable] = exponent;
}

Monomial::Monomial(double coefficient, int exponent)
{
    *this = Monomial(std::pow(coefficient, exponent));
}

Monomial::Monomial(double coefficient, const map& vars)
{
    this->coefficient = ((coefficient != 0.0) ? coefficient : 1.0);
    for(auto& var : vars)
    {
        char variable = (isAlpha(var.first) ? var.first : 0);
        int exponent = ((var.second >= 0) ? var.second : 1);
        if(variable != 0 && exponent != 0)
            variables_exponents[variable] = exponent;
    }
}

Monomial::Monomial(char variable)
{
    *this = Monomial(1, variable);
}

Monomial::Monomial(char variable, int exponent)
{
    *this = Monomial(1, variable, exponent);
}

Monomial::Monomial(const map& vars)
{
    *this = Monomial(1, vars);
}

Monomial::Monomial(const Monomial& m)
{
    coefficient = m.coefficient;
    variables_exponents = m.variables_exponents;
}

Monomial& Monomial::operator= (const Monomial& m)
{
    coefficient = m.coefficient;
    variables_exponents = m.variables_exponents;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Monomial& m)
{
    if(m.coefficient == 0.0)
    {
        out << 0;
        return out;
    }
    if(m.coefficient != 1.0 || m.variables_exponents.empty())
        out << m.coefficient;
    for(auto it{ m.variables_exponents.begin() }; it != m.variables_exponents.end(); ++it)
    {
        out << it->first;
        if(it->second != 1)
        {
            out << '^' << it->second;
            if((++it) != m.variables_exponents.end())
                out << '.';
            --it;
        }
    }
    return out;
}

std::istream& operator>> (std::istream& in, Monomial& m)
{
    std::string input{};
    std::getline(in >> std::ws, input);
    std::istringstream ss{ input };
    ss >> m.coefficient;
    if(ss.fail())
    {
        ss.clear();
        m.coefficient = 1.0;
    }
    while(!ss.eof())
    {
        char variable{};
        ss >> variable;
        char powerSign{};
        ss >> powerSign;
        if(ss.eof() && isAlpha(variable))
        {
            m.variables_exponents[variable] = 1;
            break;
        }
        if(isAlpha(powerSign))
        {
            m.variables_exponents[variable] = 1;
            ss.putback(powerSign);
        }
        else if(powerSign == '^')
        {
            int exponent{};
            ss >> exponent;
            exponent = ((exponent >= 0) ? exponent : 1);
            if(variable != 0 && exponent != 0)
                m.variables_exponents[variable] = exponent;
        }
        else
        {
            std::cerr << "Error! input only ^ or a variable!\n";
            std::exit(1);
        }
    }

    return in;
}

Monomial Monomial::operator+ (const Monomial& m2) const
{
    Monomial m3;
    if(variables_exponents != m2.variables_exponents)
    {
        std::cerr << "Error: Can not add these two!\n";
        return m3;
    }
    m3.coefficient = coefficient + m2.coefficient;
    return m3;
}

Monomial& Monomial::operator+= (const Monomial& m2)
{
    if(variables_exponents != m2.variables_exponents)
    {
        std::cerr << "Error: Can not add these two!\n";
        return *this;
    }
    this->coefficient += m2.coefficient;
    return *this;
}

Monomial Monomial::operator- (const Monomial& m2) const
{
    Monomial m3;
    if(variables_exponents != m2.variables_exponents)
    {
        std::cerr << "Error: Can not substract these two!\n";
        return m3;
    }
    m3.coefficient = coefficient - m2.coefficient;
    return m3;
}

Monomial Monomial::operator* (const Monomial& m2) const
{
    Monomial m3;
    m3.coefficient = coefficient * m2.coefficient;
    for(auto it{ variables_exponents.begin() }; it != variables_exponents.end(); ++it)
        if(m2.variables_exponents.contains(it->first))
            m3.variables_exponents[it->first] = it->second + m2.variables_exponents.at(it->first);

    for(auto it{ m2.variables_exponents.begin() }; it != m2.variables_exponents.end(); ++it)
        if(!m3.variables_exponents.contains(it->first))
            m3.variables_exponents[it->first] = it->second;

    for(auto it{ variables_exponents.begin() }; it != variables_exponents.end(); ++it)
        if(!m3.variables_exponents.contains(it->first))
            m3.variables_exponents[it->first] = it->second;
    return m3;
}

bool Monomial::operator== (const Monomial& m2) const
{
    return((coefficient == m2.coefficient) && (variables_exponents == m2.variables_exponents));
}

bool Monomial::operator!= (const Monomial& m2) const
{
    return((coefficient != m2.coefficient) && (variables_exponents != m2.variables_exponents));
}

#include "Monomial.h"
#include "Polynomial.h"
#include <iostream>

int main()
{
    Monomial m1(2, {{'x', 2}, {'y', 2}});
    Monomial m2(5.2, {{'x', 2}, {'y', 2}});
    Polynomial p1({m1, m2});
    std::cout << "p1 = " << p1 << '\n';
    Monomial m3(3, {{'x', 1}, {'y', 2}});
    Polynomial p2({m1, m3});
    std::cout << "p2 = " << p2 << '\n';
    std::cout << (p1 * p2) << '\n';
//    p2.resize(1);
//    std::cin >> p2;
//    std::cout << std::boolalpha;
//    std::cout << (p2 == p1);


    return 0;
}

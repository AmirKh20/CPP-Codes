#include "Matrix.h"
#include "SparseMatrix.h"
#include <iostream>

int main()
{
//    Matrix<double> m1(3, 3);
//    m1 = {{1, 0, 2}, {0, 55, 0}};
////    Matrix<int> m2(m1);
//    std::cin >> m1;
//    std::cout << m1.getDeterminant() << '\n';
//    Matrix m2(m1);
//    std::cout << (m1+m2) << '\n';
//    std::cout << std::boolalpha << '\n';
//    std::cout << m1.isUpperTriangular() << '\n';
//    std::cout << m1.isLowerTriangular() << '\n';
//    std::cout << m1.isSparse() << '\n';
//    Matrix<int> m3;
//    std::cin >> m3;
//    std::cout << m3 << '\n';
//    try
//    {
//        std::cout << (m1 + m3) << '\n';
//    }
//    catch(const std::exception& e)
//    {
//        std::cerr << e.what() << '\n';
//    }
//    std::cout << m1 << '\n';
//    std::cout << m1.getTranspose() << '\n';
//    m1 = m2;
//    std::cout << m1 << '\n';
//    Matrix<double> m3({{1.2, 2.1}, {3.5, 4.4}});
//    Matrix<char> m4({{'a', 'b'}, {'A', 'B'}});
//    std::cout << static_cast<Matrix<int>>(m4) << '\n';
//    std::cout << (m3 * static_cast<Matrix<double>>(m1) * 2) << '\n';
//
    SparseMatrix<int> sp1({{1, 0, 2}, {0, 55, 0}});
    std::cout << sp1 << '\n';
    std::cout << sp1.getTranspose() << '\n';
//
//    SparseMatrix<int> sp2({{1, 0, 3}, {0, 60, 1}});
//    std::cout << sp2 << '\n';
//
//    std::cout << (sp1 * sp2) << '\n';


    return 0;
}

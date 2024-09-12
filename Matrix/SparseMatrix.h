#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "Matrix.h"
#include <cstdlib>
#include <algorithm>
using std::size_t;

template<typename T>
class SparseMatrix : public Matrix<T>
{
public:
    SparseMatrix(const Matrix<T>& m);
    SparseMatrix(const SparseMatrix<T>& sp2);
    SparseMatrix(size_t r, size_t c);
    SparseMatrix<T> operator+(const SparseMatrix<T>& sp2) const;
    /*TODO SparseMatrix<T> operator*(const SparseMatrix<T>& sp2) const;*/
    SparseMatrix<T> getTranspose() const;
};

template<typename T>
SparseMatrix<T>::SparseMatrix(const Matrix<T>& m) : Matrix<T>(1, 3)
{
    this->matrix[0][0] = m.getRow();
    this->matrix[0][1] = m.getCol();
    for(size_t i{ 0 }; i < m.getRow(); i++)
        for(size_t j{ 0 }; j < m.getCol(); j++)
            if(m.getMatrix()[i][j])
                this->push_back({static_cast<T>(i), static_cast<T>(j), m.getMatrix()[i][j]});
    this->matrix[0][2] = this->row - 1;
}

template<typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& sp2) : Matrix<T>(sp2) {}

template<typename T>
SparseMatrix<T>::SparseMatrix(size_t r, size_t c) : Matrix<T>(r, c) {}

template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& sp2) const
{
    SparseMatrix<T> sp3(1, 3);
    const SparseMatrix<T>& sp1{ *this };
    sp3[0][0] = sp1[0][0];
    sp3[0][1] = sp1[0][1];
    size_t i1{ 1 };
    size_t i2{ 1 };
    while(i1 < sp1.row && i2 < sp2.row)
    {
        if(sp1[i1][0] < sp2[i2][0])
            sp3.push_back(sp1[i1++], 3);
        else if(sp1[i1][0] > sp2[i2][0])
            sp3.push_back(sp2[i2++], 3);
        else
        {
            if(sp1[i1][1] < sp2[i2][1])
                sp3.push_back(sp1[i1++], 3);
            else if(sp1[i1][1] > sp2[i2][1])
                sp3.push_back(sp2[i2++], 3);
            else
            {
                if(sp1[i1][2] + sp2[i2][2] != 0)
                    sp3.push_back({sp1[i1][0], sp2[i2][1], sp1[i1][2] + sp2[i2][2]});
                i1++;
                i2++;
            }
        }
    }
    while(i1 < sp1.row)
        sp3.push_back(sp1[i1++], 3);
    while(i2 < sp2.row)
        sp3.push_back(sp2[i2++], 3);
    sp3[0][2] = sp3.row - 1;

    return sp3;
}

/*TODO
template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix<T>& sp2) const
{
}
*/

template<typename T>
SparseMatrix<T> SparseMatrix<T>::getTranspose() const
{
    //Fast Transpose
    size_t originalMatrixCol{ static_cast<size_t>(this->matrix[0][1]) };

    int* countArray{ new int[originalMatrixCol]{} };
    for(size_t i{ 1 }; i < this->row; i++)
        countArray[this->matrix[i][1]]++;

    int* indexAarray{ new int[originalMatrixCol+1]{} };
    indexAarray[0] = 1;
    for(size_t i{ 1 }; i <= originalMatrixCol; i++)
        indexAarray[i] = indexAarray[i-1] + countArray[i-1];
    delete[] countArray;

    SparseMatrix<T> transMatrix(this->row, this->col);
    transMatrix[0][0] = this->matrix[0][1];
    transMatrix[0][1] = this->matrix[0][0];
    transMatrix[0][2] = this->matrix[0][2];

    for(size_t i{ 1 }; i < this->row; i++)
    {
        int& loc{ indexAarray[this->matrix[i][1]] };
        transMatrix[loc][0] = this->matrix[i][1];
        transMatrix[loc][1] = this->matrix[i][0];
        transMatrix[loc][2] = this->matrix[i][2];
        loc++;
    }
    delete[] indexAarray;
    return transMatrix;

    //Normal Transpose
    /*
    SparseMatrix<T> transMatrix(*this);
    for(size_t i{ 0 }; i < transMatrix.row; i++)
        std::swap(transMatrix[i][0], transMatrix[i][1]);

    auto isSorted{
        [](T* firstRow, T* secondRow)
        {
            return(firstRow[0] < secondRow[0]);
        }
    };

    std::sort(transMatrix.matrix + 1, transMatrix.matrix + this->row, isSorted);

    return transMatrix;
    */
}

#endif

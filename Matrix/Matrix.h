#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <initializer_list>
#include <exception>
using std::size_t;

template<typename T>
class Matrix;

template<typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& m);

template<typename T>
class Matrix
{
    friend std::istream& operator>> <T>(std::istream& in, Matrix<T>& m);

protected:
    T** matrix{ nullptr };
    size_t row{};
    size_t col{};

public:
    Matrix(){};
    Matrix(size_t r, size_t c);
    Matrix(const Matrix<T>& m2);
    Matrix(const std::initializer_list<std::initializer_list<T>>& il);
    template<typename U>
    Matrix(const Matrix<U>& m2);
    ~Matrix();
    size_t getRow() const;
    size_t getCol() const;
    const T* const* getMatrix() const;
    Matrix<T>& operator=(const Matrix<T>& m2);
    Matrix<T> operator+(const Matrix<T>& m2) const;
    Matrix<T> operator-(const Matrix<T>& m2) const;
    Matrix<T> operator*(const Matrix<T>& m2) const;
    Matrix<T> operator*(const T& value) const;
    T* operator[](size_t index);
    T* operator[](size_t index) const;
    void push_back(const std::initializer_list<T>& il);
    void push_back(const T* list, size_t size);
    Matrix<T> getTranspose() const;
    bool isUpperTriangular() const;
    bool isLowerTriangular() const;
    bool isSparse() const;
    T getDeterminant() const;
};

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c)
{
    if((r == 0) || (c == 0))
        throw std::invalid_argument("Rows and columns must be non-zero!");
    matrix = new T*[r];
    for(size_t i{ 0 }; i < r; i++)
        matrix[i] = new T[c]{};
    row = r;
    col = c;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m2) : Matrix<T>(m2.row, m2.col)
{
    for(size_t i{ 0 }; i < m2.row; i++)
        for(size_t j{ 0 }; j < m2.col; j++)
            matrix[i][j] = m2.matrix[i][j];
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& il) : Matrix<T>(il.size(), il.begin()->size())
{
    for(size_t i{ 0 }; auto& rowItem : il)
    {
        for(size_t j{ 0 }; auto& item : rowItem)
        {
            matrix[i][j] = item;
            j++;
        }
        i++;
    }
}

template<typename T>
template<typename U>
Matrix<T>::Matrix(const Matrix<U>& m2) : Matrix<T>(m2.getRow(), m2.getCol())
{
    for(size_t i{ 0 }; i < m2.getRow(); i++)
        for(size_t j{ 0 }; j < m2.getCol(); j++)
            matrix[i][j] = static_cast<T>(m2.getMatrix()[i][j]);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m2)
{
    for(size_t i{ 0 }; i < row; i++)
        delete[] matrix[i];
    delete[] matrix;

    matrix = new T*[m2.row];
    for(size_t i{ 0 }; i < m2.row; i++)
        matrix[i] = new T[m2.col]{};
    row = m2.row;
    col = m2.col;

    for(size_t i{ 0 }; i < m2.row; i++)
        for(size_t j{ 0 }; j < m2.col; j++)
            matrix[i][j] = m2.matrix[i][j];
    return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
    for(size_t i{ 0 }; i < row; i++)
        delete[] matrix[i];
    delete[] matrix;
}

template<typename T>
size_t Matrix<T>::getRow() const
{
    return row;
}

template<typename T>
size_t Matrix<T>::getCol() const
{
    return col;
}

template<typename T>
const T* const* Matrix<T>::getMatrix() const
{
    return matrix;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
{
    for(size_t i{ 0 }; i < m.getRow(); i++)
    {
        for(size_t j{ 0 }; j < m.getCol(); j++)
            out << m[i][j] << ' ';
        out << '\n';
    }
    return out;
}

template<typename T>
T enterFunction(const char* msg = "Enter: ")
{
    T var{};
    std::cout << msg;
    std::cin >> var;
    return var;
}

template<typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& m)
{
    if((m.row == 0) || (m.col == 0))
    {
        auto newRow{ enterFunction<size_t>("Enter the length of rows: ") };
        auto newCol{ enterFunction<size_t>("Enter the length of columns: ") };
        m = Matrix<T>(newRow, newCol);
    }

    for(size_t i{ 0 }; i < m.row; i++)
        for(size_t j{ 0 }; j < m.col; j++)
            in >> m[i][j];
    return in;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m2) const
{
    if(this->row != m2.row || this->col != m2.col)
        throw std::length_error("rows and columns must be equal!");

    Matrix<T> m3(this->row, this->col);
    for(size_t i{ 0 }; i < m3.row; i++)
        for(size_t j{ 0 }; j < m3.col; j++)
            m3.matrix[i][j] = this->matrix[i][j] + m2.matrix[i][j];
    return m3;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m2) const
{
    if(this->row != m2.row || this->col != m2.col)
        throw std::length_error("rows and columns must be equal!");

    Matrix<T> m3(this->row, this->col);
    for(size_t i{ 0 }; i < m3.row; i++)
        for(size_t j{ 0 }; j < m3.col; j++)
            m3.matrix[i][j] = this->matrix[i][j] - m2.matrix[i][j];
    return m3;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m2) const
{
    if(this->col != m2.row)
        throw std::length_error("first matrix columns must be equal to second matrix rows!");

    Matrix<T> m3(this->row, m2.col);
    for(size_t i{ 0 }; i < m3.row; i++)
        for(size_t j{ 0 }; j < m3.col; j++)
            for(size_t k{ 0 }; k < this->col; k++)
                m3.matrix[i][j] += this->matrix[i][k] * m2.matrix[k][j];
    return m3;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& value) const
{
    Matrix<T> m3(row, col);
    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            m3.matrix[i][j] = matrix[i][j] * value;
    return m3;
}

template<typename T>
T* Matrix<T>::operator[](size_t index)
{
    return matrix[index];
}

template<typename T>
T* Matrix<T>::operator[](size_t index) const
{
    return matrix[index];
}

template<typename T>
void Matrix<T>::push_back(const std::initializer_list<T>& il)
{
    if(il.size() != this->col)
        return;

    T** newMatrix{ new T*[row+1] };
    for(size_t i{ 0 }; i < row+1; i++)
        newMatrix[i] = new T[col]{};

    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            newMatrix[i][j] = matrix[i][j];
    for(size_t j{ 0 }; auto& item : il)
    {
        newMatrix[row][j] = item;
        j++;
    }

    for(size_t i{ 0 }; i < row; i++)
        delete[] matrix[i];
    delete[] matrix;

    matrix = newMatrix;
    row++;
}

template<typename T>
void Matrix<T>::push_back(const T* list, size_t size)
{
    if((size != this->col) && (this->col != 0))
        return;
    if(this->col == 0)
        this->col = size;

    T** newMatrix{ new T*[row+1] };
    for(size_t i{ 0 }; i < row+1; i++)
        newMatrix[i] = new T[col]{};

    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            newMatrix[i][j] = matrix[i][j];

    for(size_t j{ 0 }; j < size; j++)
        newMatrix[row][j] = list[j];

    for(size_t i{ 0 }; i < row; i++)
        delete[] matrix[i];
    delete[] matrix;

    matrix = newMatrix;
    row++;
}

template<typename T>
Matrix<T> Matrix<T>::getTranspose() const
{
    Matrix<T> transMatrix(col, row);

    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            transMatrix[j][i] = matrix[i][j];

    return transMatrix;
}

template<typename T>
bool Matrix<T>::isUpperTriangular() const
{
    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            if((i > j) && matrix[i][j])
                return false;
    return true;
}

template<typename T>
bool Matrix<T>::isLowerTriangular() const
{
    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            if((i < j) && matrix[i][j])
                return false;
    return true;
}

template<typename T>
bool Matrix<T>::isSparse() const
{
    int count{ 0 };
    for(size_t i{ 0 }; i < row; i++)
        for(size_t j{ 0 }; j < col; j++)
            if(!matrix[i][j])
                count++;
    return(count > (static_cast<int>(row * col) / 2));
}

template<typename T>
T Matrix<T>::getDeterminant() const
{
    if(this->row != this->col)
        throw std::length_error("# of rows and # of columns must be equal!");

    if(this->row == 2 && this->col == 2)
        return( (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]) );

    auto M{
        [](size_t i_index, size_t j_index, const Matrix<T>& m1)
        {
            Matrix<T> m2;
            for(size_t i{ 0 }; i < m1.row; i++)
            {
                if(i == i_index)
                    continue;
                T* arr{ new T[m1.col-1]{} };
                for(size_t j{ 0 }, k{ 0 }; j < m1.col; j++)
                {
                    if(j == j_index)
                        continue;
                    arr[k] = m1[i][j];
                    k++;
                }
                m2.push_back(arr, m1.col-1);
                delete[] arr;
            }
            return m2;
        }
    };
    T determinant{};
    for(size_t j{ 0 }; j < this->col; j++)
    {
        if((j % 2) == 0)
            determinant += matrix[0][j] * M(0, j, *this).getDeterminant();
        else
            determinant += (-matrix[0][j]) * M(0, j, *this).getDeterminant();

    }
    return determinant;
}

#endif

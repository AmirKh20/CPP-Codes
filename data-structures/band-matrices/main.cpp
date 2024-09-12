#include <iostream>
#include <vector>

using std::vector;

class BandMatrix
{
    vector<int> vec{};
    char kind{};
    size_t matrixSize{};

public:
    BandMatrix(size_t size, char kind);
    BandMatrix(const BandMatrix& m);
    friend std::istream& operator>> (std::istream& in, BandMatrix& m);
    friend std::ostream& operator<< (std::ostream& out, const BandMatrix& m);

    BandMatrix transpose() const;
    int determinant() const;
};

BandMatrix::BandMatrix(size_t size, char kind)
{
    if(kind != 'l' && kind != 'u' && kind != 't')
        throw std::invalid_argument("Wrong kind. Use only 'l' for lower-triangular or 'u' for upper-triangular or 't' for tridiagonal");
    if(kind == 't')
        vec.resize(size + 2*(size - 1));
    else
        vec.resize(size * (size + 1) / 2);
    matrixSize = size;
    this -> kind = kind;
}

BandMatrix::BandMatrix(const BandMatrix& m)
{
    vec = m.vec;
    kind = m.kind;
    matrixSize = m.matrixSize;
}

std::istream& operator>> (std::istream& in, BandMatrix& m)
{
    for(auto& el : m.vec)
        in >> el;
    return in;
}

std::ostream& operator<< (std::ostream& out, const BandMatrix& m)
{
    if(m.kind == 'u')
    {
        size_t vec_i{ 0 };
        for(size_t i{ 1 }; i <= m.matrixSize; i++)
        {
            for(size_t j{ 1 }; j <= m.matrixSize; j++)
            {
                if(i <= j)
                    out << m.vec[vec_i++] << ' ';
                else
                    out << "0 ";
            }
            out << '\n';
        }
    }
    else if(m.kind == 'l')
    {
        size_t vec_i{ 0 };
        for(size_t i{ 1 }; i <= m.matrixSize; i++)
        {
            for(size_t j{ 1 }; j <= m.matrixSize; j++)
            {
                if(i >= j)
                    out << m.vec[vec_i++] << ' ';
                else
                    out << "0 ";
            }
            out << '\n';
        }
    }
    else
    {
        size_t vec_i{ 0 };
        for(size_t i{ 1 }; i <= m.matrixSize; i++)
        {
            for(size_t j{ 1 }; j <= m.matrixSize; j++)
            {
                if((i == j) || (i+1 == j) || (i-1 == j))
                    out << m.vec[vec_i++] << ' ';
                else
                    out << "0 ";
            }
            out << '\n';
        }
    }
    return out;
}

BandMatrix BandMatrix::transpose() const
{
    BandMatrix m_t(*this);
    if(kind != 't')
    {
        m_t.kind = ((kind == 'u') ? 'l' : 'u');
        return m_t;
    }

    for(size_t i{ 1 }; i < m_t.vec.size(); i += 3)
    {
        int tmp{ m_t.vec[i] };
        m_t.vec[i] = m_t.vec[i+1];
        m_t.vec[i+1] = tmp;
    }
    return m_t;
}

int continuant(const vector<int>& vec, int n)
{
    if(n < 1)
        return 1;
    if(n == 1)
        return vec[1];
    return vec[n] * continuant(vec, n-3) - vec[n-2] * vec[n-1] * continuant(vec, n-6);
}

int BandMatrix::determinant() const
{
    int det{ 1 };
    if(kind == 'l')
    {
        det *= vec[0];
        size_t vec_i{ 0 };
        for(int step = 2; step <= matrixSize; step++)
        {
            det *= vec[vec_i += step];
        }
        return det;
    }
    if(kind == 'u')
    {
        size_t vec_i{ 0 };
        for(int step = matrixSize; step >= 1; step--)
        {
            det *= vec[vec_i];
            vec_i += step;
        }
        return det;
    }

    vector<int> v2(vec);
    v2.insert(v2.begin(), 0);
    return continuant(v2, vec.size());
}

int main()
{
    BandMatrix m(4, 't');
    // 1 4 3 4 1 2 3 4 1 3
    std::cin >> m;
    std::cout << m << '\n';
    std::cout << m.determinant() << '\n';

    BandMatrix m2(3, 'l');
    // 1 2 3 4 5 6
    std::cin >> m2;
    std::cout << m2 << '\n';
    std::cout << m2.determinant() << '\n';

    std::cout << m2.transpose() << '\n';
    std::cout << m2.transpose().determinant() << '\n';
    return 0;
}

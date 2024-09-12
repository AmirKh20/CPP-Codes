#include <iostream>

class Matrix
{
    friend std::istream& operator>> (std::istream& in, Matrix& m);
    friend std::ostream& operator<< (std::ostream& out, const Matrix& m);
    friend Matrix operator+ (const Matrix& m1, const Matrix& m2);
    friend Matrix operator* (const Matrix& m1, const Matrix& m2);
    int arr[3][3];

    public:
    Matrix();
    Matrix getTransposed() const;
    bool isSparce() const;
    bool operator==(const Matrix& m2) const;
    bool isBalaMosal() const;
    Matrix operator++(int);
};

Matrix::Matrix()
{
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            arr[i][j] = 0;
}

Matrix Matrix::getTransposed() const
{
    Matrix m;
    for(int j{ 0 }; j < 3; j++)
        for(int i{ 0 }; i < 3; i++)
            m.arr[j][i] = arr[i][j];
    return m;
}

bool Matrix::isSparce() const
{
    int c{ 0 };
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            if(arr[i][j] == 0)
                c++;
    return(c > 4);
}

std::istream& operator>> (std::istream& in, Matrix& m)
{
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            in >> m.arr[i][j];
    return in;
}

std::ostream& operator<< (std::ostream& out, const Matrix& m)
{
    for(int i{ 0 }; i < 3; i++)
    {
        for(int j{ 0 }; j < 3; j++)
            out << m.arr[i][j] << ' ';
        out << '\n';
    }
    return out;
}

Matrix operator+ (const Matrix& m1, const Matrix& m2)
{
    Matrix m3;
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            m3.arr[i][j] = m1.arr[i][j] + m2.arr[i][j];
    return m3;
}

Matrix operator* (const Matrix& m1, const Matrix& m2)
{
    Matrix m3;
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            m3.arr[i][j] = m1.arr[i][j] * m2.arr[i][j];
    return m3;
}

bool Matrix::operator==(const Matrix& m2) const
{
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            if(arr[i][j] != m2.arr[i][j])
                return false;
    return true;
}

Matrix Matrix::operator++(int)
{
    Matrix m;
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            m.arr[i][j] = arr[i][j]++;
    return m;
}

bool Matrix::isBalaMosal() const
{
    for(int i{ 0 }; i < 3; i++)
        for(int j{ 0 }; j < 3; j++)
            if(i > j && arr[i][j] != 0)
                    return false;
    return true;
}

int main()
{
    using std::cin;
    using std::cout;
    Matrix m1;
    cin >> m1;

    Matrix m2;
    cin >> m2;
    cout << "m1 + m2 = \n" << (m1 + m2);
    cout << "m1 * m2 = \n" << (m1 * m2);
    cout << "Transpose of m1 = \n" << m1.getTransposed();
    Matrix m3;
    cout << "Enter m3:\n";
    cin >> m3;
    cout << std::boolalpha;
    cout << "m3 Is sparce? " << m3.isSparce() << '\n';
    cout << "m1 == m2? " << (m1 == m2) << '\n';

    cout << "m1 = \n" << m1++;
    cout << "after ++\n" << m1;

    cout << "m3 is bala mosalasi? " << m3.isBalaMosal() << '\n';


    return 0;
}

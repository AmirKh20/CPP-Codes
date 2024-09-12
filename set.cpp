#include <iostream>
#include <initializer_list>
#include <cmath>
#include <utility>
using std::size_t;

template<typename T>
class Set;

template<typename T>
std::istream& operator>>(std::istream& in, Set<T>& s);

template<typename T>
class Set
{
    friend std::istream& operator>> <T>(std::istream& in, Set<T>& s);

private:
    T* arr{ nullptr };
    size_t size{};

public:
    Set(){}
    Set(size_t size);
    Set(std::initializer_list<T> il);
    Set(const Set<T>& s2);
    template<typename U>
    Set(const Set<U>& s2);
    ~Set();
    Set<T>& operator=(const Set<T>& s2);
    T* begin();
    T* begin() const;
    T* end();
    T* end() const;
    size_t getSize() const;
    bool contains(const T& value) const;
    void insert(const T& value);
    void insert(const std::initializer_list<T>& il);
    Set<T> operator&(const Set<T>& s2) const;
    Set<T> operator|(const Set<T>& s2) const;
    Set<T> operator-(const Set<T>& s2) const;
    Set<std::pair<T,T>> operator*(const Set<T>& s2) const;
    Set<Set<T>> getPowerSet() const;
    bool operator<=(const Set<T>& s2) const;
    bool operator==(const Set<T>& s2) const;
    T& operator[](size_t index);
    T& operator[](size_t index) const;
};

template<typename T>
Set<T>::Set(size_t size)
{
    arr = new T[size]{};
    this->size = size;
}

template<typename T>
Set<T>::Set(std::initializer_list<T> il)
{
    for(auto item : il)
        this->insert(item);
}

template<typename T>
Set<T>::Set(const Set<T>& s2)
{
    arr = new T[s2.size]{};
    this->size = s2.size;
    for(auto it1{ this->begin() }, it2{ s2.begin() }; it1 != this->end(); it1++, it2++)
        *it1 = *it2;
}

template<typename T>
template<typename U>
Set<T>::Set(const Set<U>& s2) : Set<T>(s2.getSize())
{
    for(auto it1{ this->begin() }, it2{ s2.begin() }; it1 != this->end(); it1++, it2++)
        *it1 = static_cast<T>(*it2);
}

template<typename T>
Set<T>::~Set()
{
    delete[] arr;
}

template<typename T>
Set<T>& Set<T>::operator=(const Set<T>& s2)
{
    delete[] arr;
    arr = new T[s2.size]{};
    this->size = s2.size;
    for(auto it1{ this->begin() }, it2{ s2.begin() }; it1 != this->end(); it1++, it2++)
        *it1 = *it2;
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Set<T>& s)
{
    out << "{ ";
    for(auto it{ s.begin() }; it != s.end(); it++)
    {
        out << *it;
        if(it != s.end()-1)
            out << ", ";
        else
            out << ' ';
    }
    out << '}';
    return out;
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Set<std::pair<U,U>>& s)
{
    out << "{ ";
    for(auto it{ s.begin() }; it != s.end(); it++)
    {
        out << "(" << it->first << ',' << it->second << ")";
        if(it != s.end()-1)
            out << ", ";
        else
            out << ' ';
    }
    out << '}';
    return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Set<T>& s)
{
    if(s.size == 0)
    {
        std::cout << "Enter size of set: ";
        std::cin >> s.size;
        s = Set<T>(s.size);
    }
    for(auto it{ s.begin() }; it != s.end(); it++)
        in >> *it;
    return in;
}

template<typename T>
T* Set<T>::begin()
{
    return arr;
}

template<typename T>
T* Set<T>::begin() const
{
    return arr;
}

template<typename T>
T* Set<T>::end()
{
    return (arr+size);
}

template<typename T>
T* Set<T>::end() const
{
    return (arr+size);
}

template<typename T>
bool Set<T>::contains(const T& value) const
{
    for(auto it{ this->begin() }; it != this->end(); ++it)
        if(*it == value)
            return true;
    return false;
}

template<typename T>
void arrayAssignment(T* arr1, const T* arr2, size_t size, size_t arr1_pos, size_t arr2_pos)
{
    for(size_t i{ arr1_pos }, j{ arr2_pos }, k{ 1 }; k <= size; i++, j++, k++)
        arr1[i] = arr2[j];
}

template<typename T>
void Set<T>::insert(const T& value)
{
    if(this->contains(value))
        return;

    T* newArr{ new T[size+1]{} };
    arrayAssignment(newArr, arr, size, 0, 0);
    newArr[size] = value;
    delete[] arr;
    arr = newArr;
    size++;
}

template<typename T>
void Set<T>::insert(const std::initializer_list<T>& il)
{
    for(auto item : il)
        this->insert(item);
}

template<typename T>
Set<T> Set<T>::operator&(const Set<T>& s2) const
{
    Set<T> s3;
    for(auto it{ this->begin() }; it != this->end(); ++it)
        if(s2.contains(*it))
            s3.insert(*it);
    return s3;
}

template<typename T>
Set<T> Set<T>::operator|(const Set<T>& s2) const
{
    Set<T> s3(*this);
    for(auto it{ s2.begin() }; it != s2.end(); ++it)
        if(!s3.contains(*it))
            s3.insert(*it);
    return s3;
}

template<typename T>
Set<T> Set<T>::operator-(const Set<T>& s2) const
{
    Set<T> s3;
    for(auto it{ this->begin() }; it != this->end(); it++)
        if(!s2.contains(*it))
            s3.insert(*it);
    return s3;
}

template<typename T>
Set<std::pair<T,T>> Set<T>::operator*(const Set<T>& s2) const
{
    Set<std::pair<T,T>> s3;
    for(auto it1{ this->begin() }; it1 != this->end(); it1++)
        for(auto it2{ s2.begin() }; it2 != s2.end(); it2++)
            s3.insert({*it1, *it2});
    return s3;
}

template<typename T>
bool Set<T>::operator<=(const Set<T>& s2) const
{
    for(auto it{ this->begin() }; it != this->end(); ++it)
        if(!s2.contains(*it))
            return false;
    return true;
}

template<typename T>
bool Set<T>::operator==(const Set<T>& s2) const
{
    if(this->size != s2.size)
        return false;
    return(*this <= s2);
}

template<typename T>
T& Set<T>::operator[](size_t index)
{
    return arr[index];
}

template<typename T>
T& Set<T>::operator[](size_t index) const
{
    return arr[index];
}

template<typename T>
Set<Set<T>> Set<T>::getPowerSet() const
{
    Set<Set<T>> s3(std::pow(2, size));

    for(size_t i{ 0 }; i < s3.getSize(); i++)
        for(size_t j{ 0 }; j < size; j++)
            if(i & (1 << j))
                s3[i].insert(arr[j]);
    return s3;
}

template<typename T>
size_t Set<T>::getSize() const
{
    return size;
}

int main()
{
    Set<int> s1( {2,3} );
    Set<double> s2( {1.5,2.3,3.4} );
    std::cout << s1 << '\n';
    std::cout << s2 << '\n';
    Set<int> s3({3, 2, 5});
    std::cout << (s1 & s3) << '\n';
    std::cout << (s1 | s3) << '\n';
    std::cout << (s1 - s3) << '\n';
    std::cout << s1.getPowerSet() << '\n';
    std::cout << (s1 * s3) << '\n';
    std::cout << std::boolalpha << '\n';
    std::cout << (s1 <= s3) << '\n';
    s1.insert({1, 2, 4});
    std::cout << s1 << '\n';
    std::cout << (s1 <= s3) << '\n';

    Set<Set<int>> ss1( {{1, 2}, {2, 3}, {3}, {4, 5, 85}, {5, 75, 95}} );
    std::cout << ss1 << '\n';

    std::cout << static_cast<Set<int>>(s2) << '\n';


	return 0;
}

#include <cstddef>
#include <istream>
#include "String.h"

void arrayAssignment(char* s1, const char* s2, size_t size, size_t s1_pos, size_t s2_pos)
{
    for(size_t i{ s1_pos }, j{ s2_pos }, k{ 1 }; k <= size; i++, j++, k++)
        s1[i] = s2[j];
}

size_t getArraySize(const char* s)
{
    size_t size{ 0 };
    for(const char* it{ s }; *it != '\0'; it++)
        size++;
    return size;
}

String::String(size_t size)
{
    str = new char[size];
    this->size = size;
}

String::String(const char* s)
{
    size = getArraySize(s);
    str = new char[size];
    arrayAssignment(str, s, size);
}

String::String(const char* s, size_t n)
{
    str = new char[n];
    size = n;
    arrayAssignment(str, s, n);
}

String::String(size_t n, char c)
{
    size = n;
    str = new char[size];
    for(size_t i{ 0 }; i < size; i++)
        str[i] = c;
}

String::String(const String& s)
{
    size = s.size;
    str = new char[size];
    arrayAssignment(str, s.str, size);
}

String::String(const String& s, size_t pos, size_t len)
{
    size = ((len != npos) ? len : s.size - pos);
    str = new char[size];
    arrayAssignment(str, s.str, size, 0, pos);
}

size_t String::getSize() const
{
    return size;
}

void String::resize(size_t newSize)
{
    char* newStr{ new char[newSize] };
    arrayAssignment(newStr, str, size);
    size = newSize;
    delete[] str;
    str = newStr;
}

char* String::begin()
{
    return str;
}

const char* String::begin() const
{
    return str;
}

char* String::end()
{
    return (str + size);
}

const char* String::end() const
{
    return (str + size);
}

bool String::isEmpty() const
{
    return(size == 0);
}

char& String::operator[](size_t pos)
{
    return str[pos];
}

const char& String::operator[](size_t pos) const
{
    return str[pos];
}

String& String::operator=(const String& s)
{
    size = s.size;
    if(str == nullptr)
        str = new char[size];
    /*TODO:out of range if this->size < s.size*/
    arrayAssignment(str, s.str, size);
    return *this;
}

std::ostream& operator<< (std::ostream& out, const String& s)
{
    for(size_t i{ 0 }; i < s.size; i++)
        out << s[i];
    out << '\n';
    return out;
}

std::istream& operator>> (std::istream& in, String& s)
{
    for(size_t i{ 0 }; i < s.size; i++)
        in >> s[i];
    return in;
}

String String::operator+ (const String& s2) const
{
    if(isEmpty())
        return s2;

    String s3(size + s2.size);
    arrayAssignment(s3.str, str, size);
    arrayAssignment(s3.str, s2.str, s2.size, size);
    return s3;
}

String String::operator+ (const char* s2) const
{
    if(isEmpty())
    {
        String s3(s2);
        return s3;
    }
    size_t s2_size{ getArraySize(s2) };
    String s3(size + s2_size);
    arrayAssignment(s3.str, str, size);
    arrayAssignment(s3.str, s2, s2_size, size);
    return s3;
}

String String::operator+ (char c) const
{
    if(isEmpty())
    {
        String s3(1, c);
        return s3;
    }

    String s3(size + 1);
    arrayAssignment(s3.str, str, size);
    s3[size] = c;
    return s3;
}

String& String::operator+= (const String& s)
{
    if(isEmpty())
    {
        *this = s;
        return *this;
    }
    char* newStr{ new char[size + s.size] };
    arrayAssignment(newStr, str, size);
    arrayAssignment(newStr, s.str, s.size, size);

    size += s.size;
    delete[] str;
    str = newStr;
    return *this;
}

String& String::operator+= (const char* s)
{
    if(isEmpty())
    {
        *this = String(s);
        return *this;
    }
    size_t s_size{ getArraySize(s) };

    char* newStr{ new char[size + s_size] };
    arrayAssignment(newStr, str, size);
    arrayAssignment(newStr, s, s_size, size);

    size += s_size;
    delete[] str;
    str = newStr;
    return *this;
}

String& String::operator+= (char c)
{
    if(isEmpty())
    {
        *this = String(1, c);
        return *this;
    }
    char* newStr{ new char[size+1] };
    arrayAssignment(newStr, str, size);
    newStr[size] = c;

    size += 1;
    delete[] str;
    str = newStr;
    return *this;
}

bool String::operator== (const String& s) const
{
    if(size != s.size)
        return false;
    for(auto it1{ begin() }, it2{ s.begin() }; it1 != end(); ++it1, ++it2)
        if(*it1 != *it2)
            return false;

    return true;
}

bool String::operator!= (const String& s) const
{
    if(size != s.size)
        return true;
    for(auto it1{ begin() }, it2{ s.begin() }; it1 != end(); ++it1, ++it2)
        if(*it1 == *it2)
            return false;
    return true;
}

String::~String()
{
    delete[] str;
    size = 0;
}

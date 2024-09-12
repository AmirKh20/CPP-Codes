#include <cstddef>
#include <istream>

#ifndef STRING_H
#define STRING_H

class String
{
    char* str{ nullptr };
    size_t size{ 0 };

    public:
    static const size_t npos{ static_cast<size_t>(-1) };

    String(){};
    String(size_t size);
    String(const char* s);
    String(const char* s, size_t n);
    String(size_t n, char c);
    String(const String& s);
    String(const String& s, size_t pos, size_t len = npos);
    ~String();

    size_t getSize() const;
    void resize(size_t newSize);
    char* begin();
    const char* begin() const;
    char* end();
    const char* end() const;
    bool isEmpty() const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;
    String& operator=(const String& s);
    friend std::ostream& operator<< (std::ostream& out, const String& s);
    friend std::istream& operator>> (std::istream& in, String& s);
    String operator+ (const String& s2) const;
    String operator+ (const char* s2) const;
    String operator+ (char c) const;
    String& operator+= (const String& s);
    String& operator+= (const char* s);
    String& operator+= (char c);
    bool operator== (const String& s) const;
    bool operator!= (const String& s) const;
};

void arrayAssignment(char* s1, const char* s2, size_t size, size_t s1_pos = 0, size_t s2_pos = 0);
size_t getArraySize(const char* s);

#endif

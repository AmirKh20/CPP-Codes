#include <iostream>
#include "String.h"

int main()
{
    String s1("amiri", 4);
    std::cout << "s1 = " << s1;

    String s2(4);
    std::cin >> s2;
    std::cout << "s2 = " << s2;

    String s3;
    s3 = s1 + s2;
    std::cout << "s3 = " << s3;

    String s4("amir");
    std::cout << "s4 = " << s4;

    String s5(s3, 2, 3);
    std::cout << "s5 = " << s5;

    String s6(5, 'a');
    std::cout << "s6 = " << s6;

    String s7("parsa");
    s7 += s2;
    std::cout << "s7+s2 = " << s7;

    String s8(s1);
    s8 += " saleh";
    std::cout << "s8 += saleh = " << s8;

    String s9(s8);
    s9 += 'a';
    std::cout << "s9 = " << s9;

    s6 += "khkhkhkh";
    std::cout << "s6 = " << s6;

    String s10("amir");
    String s11;
    s11 = s10 + 'a';
    std::cout << "s10 + 'a' = " << s11;

    std::cout << "size of s6 = " << s6.getSize() << '\n';
    s6.resize(7);
    std::cout << "s6 after resize(7) = " << s6;
    std::cout << "size of s6 = " << s6.getSize() << '\n';
    std::cout << "s1 is equal to s4? " << (s1 == s4) << '\n';
    std::cout << "s2 is not equal to s4? " << (s2 != s4) << '\n';

    return 0;
}

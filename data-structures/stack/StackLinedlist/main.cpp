#include "Stack.h"
#include <iostream>

int main()
{
    Stack s;
    s.push(1);
    s.push(3);
    s.push(4);

    std::cout << s.top() << '\n';

    Stack s2(s);
    std::cout << "s2 = " << s2 << '\n';

    s2 = s;
    std::cout << "s = " << s << '\n';
    std::cout << "s2 = " << s2 << '\n';
    //std::cout << s.top() << '\n';

    return 0;
}

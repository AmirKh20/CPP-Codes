#include "List.h"
#include <iostream>

int main()
{
    List l1(1);
    l1.push_back(2);
    l1.push_back(4);
    l1.push_back(5);

    std::cout << l1.min() << '\n';
    std::cout << l1.max() << '\n';
    std::cout << l1.avg() << '\n';

    List l2;
    l2.push_back(1);
    l2.push_back(3);
    l2.push_back(6);

    std::cout << sortedMerge(l1, l2) << '\n';

    List l3;
    l3.push_back(15);
    l3.push_back(5);
    l3.push_back(10);
    l3.push_back(2);
    l3.push_back(1);

    std::cout << l3 << '\n';
    l3.sort();
    std::cout << l3 << '\n';

    return 0;
}

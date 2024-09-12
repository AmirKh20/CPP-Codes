#include "bst.h"
#include <iostream>

int main()
{
    BST bst1({'S', 'E', 'A', 'X', 'R', 'C', 'H', 'M'});
    BST bst2(bst1);

    std::cout << "bst1: " << bst1 << '\n';
    std::cout << std::boolalpha;
    std::cout << bst1.contains('H') << '\n';
    bst1.remove('H');
    std::cout << "bst1: " << bst1 << '\n';
    std::cout << bst1.contains('H') << '\n';

    std::cout << "bst2: " << bst2 << '\n';

    std::cout << "bst2 min: " << bst2.min() << '\n';
    std::cout << "bst2 max: " << bst2.max() << '\n';

    bst1.remove('H');
    bst1 = bst2;
    std::cout << "bst1: " << bst1 << '\n';


    return 0;
}

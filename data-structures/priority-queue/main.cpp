#include "priority_queue.h"
#include <iostream>

class cmp /* example Compare class */
{
public:
    bool operator()(int a, int b)
    {
        return (a % 2 == 0 && b % 2 != 0);
    }
};

int main()
{
    PriorityQueue<int, std::greater<int>> pq1;
    pq1.push(3);
    pq1.push(1);
    pq1.push(2);
    pq1.push(0);
    std::cout << pq1.top() << '\n';
    std::cout << pq1.pop() << '\n';
    std::cout << pq1.top() << '\n';
    pq1.push(4);
    pq1.push(8);
    pq1.push(7);

    std::cout << '\n' << pq1 << '\n';

    PriorityQueue<int, cmp> pq2;
    pq2.push(3);
    pq2.push(1);
    pq2.push(2);
    pq2.push(0);
    std::cout << pq2.top() << '\n';
    std::cout << pq2.pop() << '\n';
    std::cout << pq2.top() << '\n';
    pq2.push(4);
    pq2.push(8);
    pq2.push(7);

    std::cout << '\n' << pq2 << '\n';

    return 0;
}

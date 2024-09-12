#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include <ostream>   /*      std::ostream    */
#include <functional>/*      std::less       */
#include <vector>    /*      std::vector     */
#include <utility>   /*      std::swap()     */
#include <cstddef>   /*      std::size_t     */
#include <stdexcept> /*    std::underflow_error() */
using std::size_t;

template<
    typename T,                  /* Elements Data Type                */
    class Compare = std::less<T> /* ascending priority is the default */
> class PriorityQueue
{
private:
    std::vector<T> vec = { 0 }; /* our vector is 1 indexed.          */
    void swim(size_t k);        /* sift-up an element at index k     */
    void sink(size_t k);        /* sift-down an element at index k   */

public:
    PriorityQueue() {}

    size_t size() const { return vec.size() - 1; } /* our vector is 1 indexed */
    bool isEmpty() const { return size() == 0; }
    T top() const { return vec[1]; }
    void push(const T& data);
    T pop();
};

template<typename T, class Compare>
void PriorityQueue<T, Compare>::swim(size_t k)
{
    while(k > 1 && Compare()(vec[k], vec[k/2]))
    {
        std::swap(vec[k], vec[k/2]);
        k /= 2;
    }
}

template<typename T, class Compare>
void PriorityQueue<T, Compare>::sink(size_t k)
{
    while(2*k <= size())
    {
        int j = 2*k;
        if(j+1 <= size() && Compare()(vec[j+1], vec[j]))
            j = j+1;
        if(Compare()(vec[k], vec[j]))
            break;
        std::swap(vec[k], vec[j]);
        k = j;
    }
}

template<typename T, class Compare>
void PriorityQueue<T, Compare>::push(const T& data)
{
    vec.push_back(data);
    swim(size());                   /* swim up the last element */
}

template<typename T, class Compare>
T PriorityQueue<T, Compare>::pop()
{
    if(isEmpty())
        throw std::underflow_error("The Queue is empty. Can not pop()");

    T topElement = top();
    std::swap(vec[1], vec[size()]); /* Swap the first element with the last element */
    vec.pop_back();
    sink(1);                        /* Sink down the first element(root)            */
    return topElement;
}

template<typename T, class Compare>
std::ostream& operator<< (std::ostream& out, PriorityQueue<T, Compare>& pq)
{
    while(!pq.isEmpty())
        out << pq.pop() << ' ';
    return out;
}

#endif /* ifndef PRIORITY_QUEUE */

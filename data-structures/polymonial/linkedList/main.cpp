#include <iostream>
#include <cstddef>

using std::size_t;

class Polynomial;

class Node
{
    friend class Polynomial;
    friend Polynomial operator+ (const Polynomial& p1, const Polynomial& p2);
    friend std::ostream& operator<< (std::ostream& out, const Polynomial& p);
    class Info
    {
        public:
        double coef{};
        int power{};
        Info(double c, int p = 0) : coef{ c }, power{ p } {}
        Info() {}
    };
    Info data{};
    Node* next{ nullptr };

public:
    Node(double c, int p = 0, Node* n = nullptr) : data(c, p), next{ n } {}
    Node(const Node& n);
};

Node::Node(const Node& n)
{
    data = n.data;
    next = nullptr;
}

class Polynomial
{
    Node* head{ nullptr };
    size_t size{};

public:
    Polynomial() {}
    Polynomial(Node n);
    void push(Node n);
    friend Polynomial operator+ (const Polynomial& p1, const Polynomial& p2);
    friend std::ostream& operator<< (std::ostream& out, const Polynomial& p);
};

Polynomial::Polynomial(Node n)
{
    head = new Node(n);
    size = 1;
}

void Polynomial::push(Node n)
{
    if(!head)
    {
        head = new Node(n);
        size = 1;
        return;
    }
    Node* tmp{ new Node(0, 0, head) };
    Node* it{ tmp };

    while(it -> next && it -> next -> data.power < n.data.power)
        it = it -> next;
    if(it -> next && it -> next -> data.power == n.data.power)
        it -> next -> data.coef += n.data.coef;
    else if(it -> next && it -> next -> data.power > n.data.power)
    {
        Node* newNode{ new Node(n.data.coef, n.data.power, it -> next) };
        if(it -> next == head)
            head = newNode;
        else
            it -> next = newNode;
    }
    else /* if(!it -> next) */
    {
        it -> next = new Node(n);
    }
    delete tmp;
    size++;
}

Polynomial operator+ (const Polynomial& p1, const Polynomial& p2)
{
    Polynomial p3;
    Node* it1{ p1.head };
    Node* it2{ p2.head };
    while(it1 && it2)
    {
        if(it1 -> data.power < it2 -> data.power)
        {
            p3.push(*it1);
            it1 = it1 -> next;
        }
        else if(it1 -> data.power > it2 -> data.power)
        {
            p3.push(*it2);
            it2 = it2 -> next;
        }
        else
        {
            double p3_coef{ it1 -> data.coef + it2 -> data.coef };
            p3.push({p3_coef, it1 -> data.power});
            it1 = it1 -> next;
            it2 = it2 -> next;
        }
    }
    while(it1)
    {
        p3.push(*it1);
        it1 = it1 -> next;
    }
    while(it2)
    {
        p3.push(*it2);
        it2 = it2 -> next;
    }
    return p3;
}

std::ostream& operator<< (std::ostream& out, const Polynomial& p)
{
    for(Node* it{ p.head }; it != nullptr; it = it -> next)
    {
        if     (it -> data.coef > 0)
            out << '+' << it -> data.coef << "x^" << it -> data.power << ' ';
        else if(it -> data.coef < 0)
            out << it -> data.coef << "x^" << it -> data.power << ' ';
    }
    return out;
}

int main()
{
    Polynomial p1({2, 3});
    p1.push({1, 2});
    p1.push({3, 5});
    p1.push({-3, 4});
    p1.push({-2, 4});
    std::cout << p1 << '\n';

    Polynomial p2({1, 3});
    p2.push({4, 4});
    std::cout << p2 << '\n';

    std::cout << (p1 + p2) << '\n';

    return 0;
}

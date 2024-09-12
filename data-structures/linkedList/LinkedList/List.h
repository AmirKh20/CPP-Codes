#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <ostream>

using std::size_t;

class List;

class Node
{
    friend class List;
    friend std::ostream& operator<< (std::ostream& out, const List& l);
    friend List sortedMerge(const List& l1, const List& l2);
    int data{};
    Node* next{ nullptr };

public:
    Node(int d, Node* n = nullptr) : data{ d }, next{ n } {}
    Node(const Node& n);
};

Node::Node(const Node& n)
{
    data = n.data;
    next = nullptr;
}

class List
{
    Node* head{ nullptr };
    Node* tail{ nullptr };
    size_t size{};
    List mergeSort();

public:
    List() {}
    List(int data);
    List(const List& l);
    List& operator= (const List& l);
    ~List();

    void push_back(int data);
    void push_front(int data);
    int front() const;
    int back() const;

    int min() const;
    int max() const;
    double avg() const;
    friend List sortedMerge(const List& l1, const List& l2);
    friend std::ostream& operator<< (std::ostream& out, const List& l);
    void sort();
};

List::List(int data)
{
    Node* newNode{ new Node(data) };
    newNode -> next = head;
    head = newNode;
    tail = head;
    size = 1;
}

List::List(const List& l)
{
    for(Node* it{ l.head }; it != nullptr; it = it -> next)
        this -> push_back(it -> data);
}

List& List::operator= (const List& l)
{
    this -> ~List();

    for(Node* it{ l.head }; it != nullptr; it = it -> next)
        this -> push_back(it -> data);

    return *this;
}

List::~List()
{
    Node* nextIter{};
    for(Node* it{ head }; it != nullptr; it = nextIter)
    {
        nextIter = it -> next;
        delete it;
    }
}

std::ostream& operator<< (std::ostream& out, const List& l)
{
    for(Node* it{ l.head }; it != nullptr; it = it -> next)
        out << it -> data << ' ';
    return out;
}

void List::push_back(int data)
{
    if(!head)
    {
        Node* newNode{ new Node(data) };
        newNode -> next = head;
        head = newNode;
        tail = head;
        size = 1;
        return;
    }
    Node* newNode{ new Node(data) };
    tail -> next = newNode;
    tail = newNode;
    size++;
}

void List::push_front(int data)
{
    Node* newNode{ new Node(data, head) };
    head = newNode;
    size++;
}

int List::front() const
{
    return head -> data;
}

int List::back() const
{
    return tail -> data;
}

int List::min() const
{
    Node* minNode{ head };
    for(Node* it{ head -> next }; it != nullptr; it = it -> next)
        if(it -> data < minNode -> data)
            minNode = it;
    return minNode -> data;
}

int List::max() const
{
    Node* maxNode{ head };
    for(Node* it{ head -> next }; it != nullptr; it = it -> next)
        if(it -> data > maxNode -> data)
            maxNode = it;
    return maxNode -> data;
}

double List::avg() const
{
    int sum{ 0 };
    for(Node* it{ head }; it != nullptr; it = it -> next)
        sum += it -> data;
    return static_cast<double>(sum) / size;
}

List sortedMerge(const List& l1, const List& l2)
{
    List l3;
    Node* it1{ l1.head };
    Node* it2{ l2.head };
    while(it1 && it2)
    {
        if     (it1 -> data <= it2 -> data)
        {
            l3.push_back(it1 -> data);
            it1 = it1 -> next;
        }
        else if(it1 -> data > it2 -> data)
        {
            l3.push_back(it2 -> data);
            it2 = it2 -> next;
        }
    }
    while(it1)
    {
        l3.push_back(it1 -> data);
        it1 = it1 -> next;
    }
    while(it2)
    {
        l3.push_back(it2 -> data);
        it2 = it2 -> next;
    }
    return l3;
}

List List::mergeSort()
{
    if(!head || !head -> next)
        return *this;

    List left_list;
    List right_list;
    Node* it{ head };
    for(int i = 1; i <= size; i++)
    {
        if(i <= size/2)
            left_list.push_back(it -> data);
        else
            right_list.push_back(it -> data);
        it = it -> next;
    }

    return sortedMerge(left_list.mergeSort(), right_list.mergeSort());
}

void List::sort()
{
    *this = this -> mergeSort();
}

#endif // LIST_H

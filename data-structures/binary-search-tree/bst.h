#ifndef BST_H
#define BST_H

#include <stdexcept>
#include <initializer_list>
#include <ostream>
#include <vector>

template<typename T> class BST;

template<typename T>
class Node
{
private:
    friend class BST<T>;

    T data{};
    Node<T>* left{ nullptr };
    Node<T>* right{ nullptr };
    Node(const T& data) : data{ data } {}
    Node(const Node<T>& node);
};

template<typename T>
Node<T>::Node(const Node<T>& node)
{
    this -> data = node.data;

    if(node.right)
        right = new Node<T>(*node.right);
    else
        right = nullptr;

    if(node.left)
        left = new Node<T>(*node.left);
    else
        left = nullptr;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const BST<T>& bst);

template<typename T>
class BST
{
private:
    Node<T>* root{ nullptr };

    Node<T>* insert(const T& data, Node<T>* node);
    Node<T>* min(Node<T>* node) const;
    Node<T>* max(Node<T>* node) const;
    Node<T>* deleteMin_without_freeing(Node<T>* node); /* This method doesn't free the memory of the minimum node on purpose. For using in the remove method */
    Node<T>* remove(const T& data, Node<T>* node);
    void inorder(std::vector<T>& vec, const Node<T>* node) const;
    friend std::ostream& operator<< <T>(std::ostream& out, const BST<T>& bst);

public:
    BST() {}
    BST(const BST<T>& bst);
    BST(const std::initializer_list<T>& il);
    ~BST();

    BST<T>& operator= (const BST<T>& bst);
    void insert(const T& data) { root = insert(data, root); }
    void remove(const T& data) { root = remove(data, root); }
    bool contains(const T& data);
    T  min() const;
    T& min();
    T  max() const;
    T& max();
    void saveToVector(std::vector<T>& vec) const;
};

template<typename T>
BST<T>::BST(const BST<T>& bst)
{
    root = new Node<T>(*bst.root);
}

template<typename T>
BST<T>& BST<T>::operator= (const BST<T>& bst)
{
    this -> ~BST();
    root = new Node<T>(*bst.root);
    return *this;
}

template<typename T>
BST<T>::BST(const std::initializer_list<T>& il)
{
    for(auto& el : il)
        insert(el);
}


template<typename T>
BST<T>::~BST()
{
    std::vector<T> vec;
    saveToVector(vec);
    while(!vec.empty())
    {
        remove(vec.back());
        vec.pop_back();
    }
}

template<typename T>
Node<T>* BST<T>::insert(const T& data, Node<T>* node)
{
    if(!node)
        return new Node<T>(data);
    if(data < node -> data)
        node -> left = insert(data, node -> left);
    else if(data > node -> data)
        node -> right = insert(data, node -> right);
    else
        throw std::invalid_argument("Duplicated Data. Can not insert()"); //TODO:show insert

    return node;
}

template<typename T>
Node<T>* BST<T>::min(Node<T>* node) const
{
    Node<T>* it{ node };
    while(it -> left)
        it = it -> left;
    return it;
}

template<typename T>
T BST<T>::min() const
{
    Node<T>* minNode{ min(root) };
    return minNode -> data;
}

template<typename T>
T& BST<T>::min()
{
    Node<T>* minNode{ min(root) };
    return minNode -> data;
}

template<typename T>
Node<T>* BST<T>::max(Node<T>* node) const
{
    Node<T>* it{ node };
    while(it -> right)
        it = it -> right;
    return it;
}

template<typename T>
T BST<T>::max() const
{
    Node<T>* maxNode{ max(root) };
    return maxNode -> data;
}

template<typename T>
T& BST<T>::max()
{
    Node<T>* maxNode{ max(root) };
    return maxNode -> data;
}

template<typename T>
Node<T>* BST<T>::deleteMin_without_freeing(Node<T>* node) /* This method doesn't free the memory of the minimum node on purpose. For using in the remove method */
{
    if(!node -> left)
        return node -> right;

    node -> left = deleteMin_without_freeing(node -> left);

    return node;
}

template<typename T>
Node<T>* BST<T>::remove(const T& data, Node<T>* node)
{
    if(!node)
        throw std::runtime_error("Data not found. Can not remove()"); //TODO

    if     (data < node -> data)
        node -> left = remove(data, node -> left);
    else if(data > node -> data)
        node -> right = remove(data, node -> right);
    else
    {
        if(!node -> left)
        {
            Node<T>* right_node{ node -> right };
            delete node;
            return right_node;
        }

        if(!node -> right)
        {
            Node<T>* left_node{ node -> left };
            delete node;
            return left_node;
        }

        Node<T>* t{ node };                     /* Create a copy of the pointer to the node which we want to delete                                             */
        node = min(node -> right);              /* change our node pointer to point to the minimum node                                                         */
        deleteMin_without_freeing(t -> right);  /* Delete the minimum node but do not free the memory(just change links), so our node pointer won't be dangling */
        node -> left = t -> left;               /* Replace our node pointer's right with the original wanted to be deleted node pointer's right                 */
        node -> right = t -> right;             /* Replace our node pointer's left with the original wanted to be deleted node pointer's left                   */
        delete t;                               /* Eventually free the memory of the original wanted to be deleted node                                         */
    }
    return node;
}

template<typename T>
void BST<T>::inorder(std::vector<T>& vec, const Node<T>* node) const
{
    if(!node)
        return;
    inorder(vec, node -> left);
    vec.push_back(node -> data);
    inorder(vec, node -> right);
}

template<typename T>
bool BST<T>::contains(const T& data)
{
    Node<T>* it{ root };
    while(it)
    {
        if     (data < it -> data)
            it = it -> left;
        else if(data > it -> data)
            it = it -> right;
        else
            return true;
    }
    return false;
}

template<typename T>
void BST<T>::saveToVector(std::vector<T>& vec) const
{
    inorder(vec, root);
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const BST<T>& bst)
{
    std::vector<T> vec;
    bst.saveToVector(vec);
    for(auto el : vec)
        out << el << ' ';
    return out;
}

#endif

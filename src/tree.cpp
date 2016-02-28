#include <iostream>
#include <random>


template <typename T>
struct TreeNode
{
    TreeNode(const T& d) : left(nullptr), right(nullptr), parent(nullptr), data(d) {}
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;
    T data;
};


template <typename T>
struct TreeNodeIterator
{
    typedef T* pointer;
    typedef T& reference;
    
    TreeNodeIterator() : node(nullptr) {}
    TreeNodeIterator(TreeNode<T>* _node) : node(_node) {}
    TreeNodeIterator(const TreeNodeIterator& t) : node(t.node) {}

    bool operator==(const TreeNodeIterator& t) { return this->node == t.node; }
    bool operator!=(const TreeNodeIterator& t) { return this->node != t.node; }
    reference operator*() const { return node->data; }
    pointer operator->() const { return &(node->data); }
    TreeNodeIterator& operator++();
    TreeNodeIterator operator++(int) { TreeNodeIterator tmp = *this; ++*this; return tmp; }
    TreeNodeIterator& operator--();
    TreeNodeIterator operator--(int) { TreeNodeIterator tmp = *this; --*this; return tmp; }

    TreeNode<T>* node;
};

template <typename T>
TreeNodeIterator<T>& TreeNodeIterator<T>::operator++()
{
    TreeNode<T>* right = node->right;
    if (right == nullptr)
    {
        TreeNode<T>* parent = node->parent;
        while (parent && node == parent->right)
        {
            node = parent;
            parent = node->parent;
        }
        node = parent;
    }
    else
    {
        while (right->left)
            right = right->left;
        node = right;
    }
    return *this;
}

template <typename T>
TreeNodeIterator<T>& TreeNodeIterator<T>::operator--()
{
    TreeNode<T>* left = node->left;
    if (left == nullptr)
    {
        TreeNode<T>* parent = node->parent;
        while (parent && node == parent->left)
        {
            node = parent;
            parent = node->parent;
        }
        node = parent;
    }
    else
    {
        while (left->right)
            left = left->right;
        node = left;
    }
    return *this;
}


template <typename T>
class Tree
{
    public:
        typedef TreeNodeIterator<T> iterator;

    public:
        Tree() : root(nullptr) {}
        Tree(const T& v) : root(nullptr) {}
        ~Tree();

    public:
        iterator search(const T& v) { return iterator(_search(v)); };
        iterator insert(const T& v);
        void remove(const T& v);
        iterator begin();
        iterator end() { return nullptr; }

    private:
        TreeNode<T>* _search(const T& v);
        void _free(TreeNode<T>* node);
        void _transplant(TreeNode<T>* node, TreeNode<T>* relpaceNode);

    private:
        TreeNode<T>* root;
};

template <typename T>
void Tree<T>::_free(TreeNode<T>* node)
{
    if (node)
    {
        _free(node->left);
        _free(node->right);
        delete node;
    }
}

template <typename T>
Tree<T>::~Tree()
{
    _free(root);
    root = nullptr;
}

template <typename T>
void Tree<T>::_transplant(TreeNode<T>* node, TreeNode<T>* replaceNode)
{
    if (node->parent == nullptr)
        root = replaceNode;
    else if (node == node->parent->left)
        node->parent->left = replaceNode;
    else
        node->parent->right = replaceNode;
    if (replaceNode)
        replaceNode->parent = node->parent;
}

template <typename T>
void Tree<T>::remove(const T& v)
{
    TreeNode<T>* node = _search(v);
    if (node == nullptr)
        return;

    if (node->left == nullptr)
        _transplant(node, node->right);
    else if (node->right == nullptr)
        _transplant(node, node->left);
    else
    {
        TreeNode<T>* next = node->right;
        while (next && next->left)
            next = next->left;
        if (next->parent != node)
        {
            _transplant(next, next->right);
            next->right = node->right;
            next->right->parent = next;
        }
        _transplant(node, next);
        next->left = node->left;
        next->left->parent = next;
    }
}

template <typename T>
TreeNode<T>* Tree<T>::_search(const T& v)
{
    TreeNode<T>* node = root;
    while (node && node->data != v)
    {
        if (v < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

template <typename T>
typename Tree<T>::iterator Tree<T>::insert(const T& v)
{
    TreeNode<T>* node = new TreeNode<T>(v);
    TreeNode<T>* ptNode = root;
    TreeNode<T>* parentNode = nullptr;
    while (ptNode)
    {
        parentNode = ptNode;
        if (v < ptNode->data)
            ptNode = ptNode->left;
        else
            ptNode = ptNode->right;
    }
    node->parent = parentNode;
    if (parentNode)
    {
        if (v < parentNode->data)
            parentNode->left = node;
        else
            parentNode->right = node;
    }
    else
    {
        root = node;
    }
    return Tree<T>::iterator(node);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::begin()
{
    TreeNode<T>* node = root;
    while (node && node->left)
        node = node->left;
    return Tree<T>::iterator(node);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Tree<T>& t)
{
    for (typename Tree<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        os << *iter << " ";
    return os;
}


int main()
{
    std::default_random_engine random(time(0));
    std::uniform_int_distribution<int> dis(1, 100);
    const size_t length = 20;
    Tree<int> tree;
    for (size_t i = 0; i < length; ++i)
    {
        const int num = dis(random);
        std::cout << num << " ";
        tree.insert(num);
    }
    std::cout << std::endl;

    int n;
    std::cin >> n; 

    tree.remove(n);

    // Tree<int>::iterator iter = tree.begin();
    // std::cout << *iter++ << std::endl;
    // std::cout << *iter-- << std::endl;
    // std::cout << *(++iter) << std::endl;
    // std::cout << *(--iter) << std::endl;

    std::cout << tree << std::endl;

    return 0;
}

#include <iostream>
#include <random>


enum RBTreeNodeColor
{
    RED,
    BLACK,
};


template <typename T>
struct RBTreeNode
{
    RBTreeNode(const T& v) : left(nullptr), right(nullptr), parent(nullptr), color(RED), data(v) {}
    RBTreeNode<T>* left;
    RBTreeNode<T>* right;
    RBTreeNode<T>* parent;
    RBTreeNodeColor color;
    T data;
};


template <typename T>
class RBTree
{
    public:
        RBTree() : root(nullptr) {}

    public:
        void insert(const T& v);

    private:
        void _left_rotate(RBTreeNode<T>* node);
        void _right_rotate(RBTreeNode<T>* node);
        void _rb_insert_fixup(RBTreeNode<T>* node);

    private:
        RBTreeNode<T>* root;
};

template <typename T>
void RBTree<T>::insert(const T& v)
{
    RBTreeNode<T>* node = new RBTreeNode<T>(v);
    RBTreeNode<T>* findNode = root;
    RBTreeNode<T>* parentNode = nullptr;
    while (findNode)
    {
        parentNode = findNode;
        if (v < findNode->data)
            findNode = findNode->left;
        else
            findNode = findNode->right;
    }
    node->parent = parentNode;
    if (parentNode == nullptr)
        root = node;
    else if (v < parentNode->data)
        parentNode->left = node;
    else
        parentNode->right = node;
    // _rb_insert_fixup(node);
}

template <typename T>
void RBTree<T>::_left_rotate(RBTreeNode<T>* node)
{
    RBTreeNode<T>* rightNode = node->right;
    node->right = rightNode->left;
    if (rightNode->left != nullptr)
        rightNode->left->parent = node;
    rightNode->parent = node->parent;
    if (node->parent == nullptr)
        root = rightNode;
    else if (node == node->parent->left)
        node->parent->left = rightNode;
    else
        node->parent->right = rightNode;
    node->parent = rightNode;
}

template <typename T>
void RBTree<T>::_right_rotate(RBTreeNode<T>* node)
{
    RBTreeNode<T>* leftNode = node->left;
    node->left = leftNode->right;
    if (leftNode->right != nullptr)
        leftNode->right->parent = node;
    leftNode->parent = node->parent;
    if (node->parent == nullptr)
        root = leftNode;
    else if (node == node->parent->left)
        node->parent->left = leftNode;
    else
        node->parent->right = leftNode;
    node->parent = leftNode;
}

template <typename T>
void RBTree<T>::_rb_insert_fixup(RBTreeNode<T>* node)
{
    while (node->parent && node->parent->color == RED)
    {
    }
    root->color = BLACK;
}


int main()
{
    return 0;
}

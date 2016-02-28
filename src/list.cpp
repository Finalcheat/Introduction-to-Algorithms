#include <iostream>


template <typename T>
struct ListNode
{
    typedef ListNode<T>* PtNode;
    PtNode prev;
    PtNode next;
    T data;
};


template <typename T>
struct ListNodeIterator
{
    typedef ListNodeIterator<T> iterator;
    typedef T* pointer;
    typedef T& reference;

    ListNodeIterator() : node(nullptr) {}
    ListNodeIterator(ListNode<T>* _node) : node(_node) {}
    ListNodeIterator(const ListNodeIterator& n) : node(n.node) {}

    bool operator==(const ListNodeIterator& n) { return this->node == n.node; }
    bool operator!=(const ListNodeIterator& n) { return this->node != n.node; }
    reference operator*() const { return node->data; }
    pointer operator->() const { return &(node->data); }
    iterator& operator++() { node = node->next; return *this; }
    iterator operator++(int) { iterator tmp = *this; ++*this; return tmp; }
    iterator& operator--() { node = node->prev; return *this; }
    iterator operator--(int) { iterator tmp = *this; --*this; return tmp; }

    ListNode<T>* node;
};


template <typename T>
class List
{
    public:
        typedef ListNodeIterator<T> iterator;

    public:
        List() : head(nullptr), tail(nullptr) {}
        List(const T& v) : head(nullptr), tail(nullptr) { insert(v); }
        ~List();

    public:
        ListNode<T>* search(const T& v);
        void insert(const T& v);
        void push(const T& v);
        void remove(const T& v);
        iterator begin() { return iterator(head); }
        iterator end() { return nullptr; }

    private:
        ListNode<T>* head;
        ListNode<T>* tail;
};


template <typename T>
List<T>::~List()
{
    while (head != tail)
    {
        ListNode<T>* node = head->next;
        delete head;
        head = node;
    }
}


template <typename T>
ListNode<T>* List<T>::search(const T& v)
{
    for (ListNode<T>* p = head; p != nullptr; p = p->next)
    {
        if (p->data == v)
            return p;
    }
    return nullptr;
}


template <typename T>
void List<T>::insert(const T& v)
{
    ListNode<T>* node = new ListNode<T>;
    node->data = v;
    node->prev = nullptr;
    node->next = nullptr;
    if (head == nullptr)
    {
        tail = head = node;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
}


template <typename T>
void List<T>::push(const T& v)
{
    ListNode<T>* node = new ListNode<T>;
    node->data = v;
    node->prev = nullptr;
    node->next = nullptr;
    if (head == nullptr)
    {
        tail = head = node;
    }
    else
    {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
}


template <typename T>
void List<T>::remove(const T& v)
{
    ListNode<T>* node = List<T>::search(v);
    if (node != nullptr)
    {
        ListNode<T>* prev = node->prev;
        ListNode<T>* next = node->next;

        if (prev != nullptr)
            prev->next = next;
        else
        {
            // delete head node
            head = next;
        }

        if (next != nullptr)
            next->prev = prev;
        else
        {
            // delete tail node
            tail = prev;
        }

        delete node;
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, List<T>& l)
{
    for (typename List<T>::iterator iter = l.begin(); iter != l.end(); ++iter)
    {
        os << *iter << " ";
    }
    return os;
}


int main()
{
    List<int> l;
    const size_t num = 10;
    for (size_t i = 0; i < num; ++i)
    {
        l.insert(i);
        std::cout << i << " ";
    }
    std::cout << std::endl;

    l.remove(3);
    l.remove(9);
    l.remove(0);

    l.push(99);

    std::cout << l << std::endl;

    return 0;
}

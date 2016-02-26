#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <ctime>


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    typename std::vector<T>::const_iterator it = v.begin();
    while (it != v.end())
        os << *it++ << " ";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& l)
{
    typename std::list<T>::const_iterator it = l.begin();
    while (it != l.end())
        os << *it++ << " ";
    return os;
}


template <typename InputIterator, typename Comp = std::less<typename std::iterator_traits<InputIterator>::value_type> >
void insertion_sort(InputIterator begin, InputIterator end, Comp comp = Comp())
{
    for (InputIterator iter = begin; iter != end; ++iter)
    {
        typename std::iterator_traits<InputIterator>::value_type v = *iter;
        InputIterator pos = iter;
        while (pos != begin && comp(v, *(std::prev(pos, 1))))
        {
            *pos = *(std::prev(pos, 1));
            --pos;
        }
        *pos = v;
    }
}


struct Goods
{
    public:
        Goods(const size_t i, const float p) : id(i), price(p) {}

    public:
        size_t id;
        float price;
};

std::ostream& operator<<(std::ostream& os, const std::vector<Goods>& gs)
{
    for (const auto& g : gs)
    {
        os << g.id << "(" << g.price << ") ";
    }
    return os;
}


int main()
{
    srand((int)time(0));
    const int length = 20;
    int *arr = new int[length];
    std::vector<int> vec(length);
    std::list<int> lists;
    std::vector<Goods> gs;
    for (int i = 0; i < length; ++i)
    {
        // [1, 100]
        const int num = rand() % 100 + 1;
        arr[i] = num;
        vec[i] = num;

        gs.push_back(Goods((i + 1), num));
        lists.push_back(num);
    }
    std::cout << vec << std::endl;

    // vector<int> insertion_sort
    insertion_sort(vec.begin(), vec.end());
    std::cout << vec << std::endl;

    // list<int> insertion_sort
    insertion_sort(lists.begin(), lists.end());
    std::cout << lists << std::endl;

    // int* insertion_sort
    insertion_sort(arr, arr + length);
    for (auto p = arr; p != arr + length; ++p)
        std::cout << *p << " ";
    std::cout << std::endl;

    std::cout << gs << std::endl;

    // vector<Goods> insertion_sort
    insertion_sort(gs.begin(), gs.end(), [](const Goods& l, const Goods& r) { return l.price < r.price; });
    std::cout << gs << std::endl;

    insertion_sort(gs.begin(), gs.end(), [](const Goods& l, const Goods& r) { return l.price > r.price; });
    std::cout << gs << std::endl;

    delete[] arr;

    return 0;
}

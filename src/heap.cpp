#include <iostream>
#include <vector>


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    typename std::vector<T>::const_iterator it = v.begin();
    while (it != v.end())
        os << *it++ << " ";
    return os;
}


template <typename InputIterator, typename Distance, typename Comp>
void heapify(InputIterator begin, InputIterator end, Distance index, Comp comp)
{
    // left = index * 2 + 1
    Distance left = (index << 1) + 1;
    // right = index * 2 + 2
    Distance right = (index << 1) + 2;

    // length
    typename std::iterator_traits<InputIterator>::difference_type length = std::distance(begin, end);
    Distance l = index;
    if (left < length && !comp(*(begin + left), *(begin + l)))
        l = left;

    if (right < length && !comp(*(begin + right), *(begin + l)))
        l = right;

    if (l != index)
    {
        typename std::iterator_traits<InputIterator>::value_type value = *(begin + l);
        *(begin + l) = *(begin + index);
        *(begin + index) = value;
        heapify(begin, end, l, comp);
    }
}


template <typename InputIterator, typename Comp>
void build_heap(InputIterator begin, InputIterator end, Comp comp) 
{
    typename std::iterator_traits<InputIterator>::difference_type length = std::distance(begin, end);
    length = length >> 1;
    while (--length >= 0)
    {
        heapify(begin, end, length, comp);
    }
}


template <typename InputIterator, typename Comp = std::less<typename std::iterator_traits<InputIterator>::value_type> >
void heap_sort(InputIterator begin, InputIterator end, Comp comp = Comp())
{
    build_heap(begin, end, comp);
    typename std::iterator_traits<InputIterator>::difference_type length = std::distance(begin, end);
    while (--length >= 0)
    {
        typename std::iterator_traits<InputIterator>::value_type value = *begin;
        *begin = *(--end);
        *end = value;
        heapify(begin, end, 0, comp);
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
    std::vector<int> vec{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::cout << vec << std::endl;

    std::vector<Goods> gs;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        gs.push_back(Goods(i + 1, vec[i]));
    }

    // heap_sort asc
    heap_sort(vec.begin(), vec.end());
    std::cout << vec << std::endl;

    // heap_sort desc
    heap_sort(vec.begin(), vec.end(), [](const int l, const int r) { return l > r; });
    std::cout << vec << std::endl;

    std::cout << gs << std::endl;

    // vector<Goods> heap_sort asc
    heap_sort(gs.begin(), gs.end(), [](const Goods& l, const Goods& r) { return l.price < r.price; }); 
    std::cout << gs << std::endl;

    // vector<Goods> heap_sort desc
    heap_sort(gs.begin(), gs.end(), [](const Goods& l, const Goods& r) { return l.price > r.price; });
    std::cout << gs << std::endl;

    return 0;
}

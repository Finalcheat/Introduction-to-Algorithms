#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


template <typename InputIterator, typename Comp>
void merge(InputIterator begin, InputIterator middle, InputIterator end, Comp comp)
{
    // copy [begin, middle)
    typename std::iterator_traits<InputIterator>::difference_type n1 = std::distance(begin, middle);
    std::vector<typename std::iterator_traits<InputIterator>::value_type> vec1(n1);
    typename std::vector<typename std::iterator_traits<InputIterator>::value_type>::iterator p1 = vec1.begin();
    std::copy(begin, middle, p1);

    // copy [middle, end)
    typename std::iterator_traits<InputIterator>::difference_type n2 = std::distance(middle, end);
    std::vector<typename std::iterator_traits<InputIterator>::value_type> vec2(n2);
    typename std::vector<typename std::iterator_traits<InputIterator>::value_type>::iterator p2 = vec2.begin();
    std::copy(middle, end, p2);

    while (n1 > 0 && n2 > 0)
    {
        if (comp(*p1, *p2))
        {
            *begin = *p1++;
            --n1;
        }
        else
        {
            *begin = *p2++;
            --n2;
        }
        ++begin;
    }

    while (n1 > 0)
    {
        *begin++ = *p1++;
        --n1;
    }

    while (n2 > 0)
    {
        *begin++ = *p2++;
        --n2;
    }
}


template <typename InputIterator, typename Comp = std::less<typename std::iterator_traits<InputIterator>::value_type> >
void merge_sort(InputIterator begin, InputIterator end, Comp comp = Comp())
{
    if (std::distance(begin, end) > 1)
    {
        typename std::iterator_traits<InputIterator>::difference_type diff = std::distance(begin, end);
        // std::cout << diff << std::endl;
        typename std::iterator_traits<InputIterator>::difference_type half = diff >> 1;
        InputIterator middle = std::next(begin, half);
        merge_sort(begin, middle, comp);
        merge_sort(middle, end, comp);
        merge(begin, middle, end, comp);
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    typename std::vector<T>::const_iterator it = v.begin();
    while (it != v.end())
        os << *it++ << " ";
    return os;
}


struct Goods
{
    public:
        Goods() : id(-1), price(-1) {}
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
    std::vector<Goods> gs;
    for (int i = 0; i < length; ++i)
    {
        // [1, 100]
        const int num = rand() % 100 + 1;
        arr[i] = num;
        vec[i] = num;
        std::cout << num << " ";

        gs.push_back(Goods((i + 1), num));
    }
    std::cout << std::endl;

    // vector<int> merge_sort
    merge_sort(vec.begin(), vec.end());
    std::cout << vec << std::endl;

    // int* merge_sort
    merge_sort(arr, arr + length);
    for (auto p = arr; p != arr + length; ++p)
        std::cout << *p << " ";
    std::cout << std::endl;

    // vector<Goods> merge_sort
    std::cout << gs << std::endl;
    merge_sort(gs.begin(), gs.end(), [](const Goods& l, const Goods& r) { return l.price < r.price; });
    std::cout << gs << std::endl;

    return 0;
}

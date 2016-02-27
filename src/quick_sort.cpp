#include <iostream>
#include <vector>
#include <random>


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    typename std::vector<T>::const_iterator it = v.begin();
    while (it != v.end())
        os << *it++ << " ";
    return os;
}


template <typename InputIterator, typename Comp = std::less<typename std::iterator_traits<InputIterator>::value_type> >
InputIterator quick_sort_partition(InputIterator begin, InputIterator end, Comp comp = Comp())
{
    typename std::iterator_traits<InputIterator>::value_type value = *(--end);
    InputIterator pos = std::prev(begin, 1);
    for (InputIterator iter = begin; iter != end; ++iter)
    {
        if (comp(*iter, value))
        {
            ++pos;
            std::swap(*pos, *iter);
        }
    }
    std::swap(*end, *(++pos));
    return pos;
}


template <typename InputIterator, typename Comp = std::less<typename std::iterator_traits<InputIterator>::value_type> >
void quick_sort(InputIterator begin, InputIterator end, Comp comp = Comp())
{
    typename std::iterator_traits<InputIterator>::difference_type length = std::distance(begin, end);
    if (length > 1)
    {
        InputIterator q = quick_sort_partition(begin, end, comp);
        // [begin, q)
        quick_sort(begin, q, comp);
        // [q, end)
        quick_sort(++q, end, comp);
    }
}


int main()
{
    std::default_random_engine random(time(0));
    const size_t length = 20;
    std::uniform_int_distribution<int> dis(1, 100);
    std::vector<int> vec;
    for (size_t i = 0; i < length; ++i)
    {
        vec.push_back(dis(random));
    }
    std::cout << vec << std::endl;

    // vector<int> quick_sort asc
    quick_sort(vec.begin(), vec.end());
    std::cout << vec << std::endl;

    // vector<int> quick_sort desc
    quick_sort(vec.begin(), vec.end(), [](const int l, const int r) { return l > r; });
    std::cout << vec << std::endl;

    return 0;
}

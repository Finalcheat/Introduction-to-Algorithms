#include <iostream>
#include <vector>
#include <list>


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


template <typename InputIterator>
int maxinum_subarray(InputIterator begin, InputIterator end)
{
    int sum = 0;
    int cur = 0;
    for (InputIterator iter = begin; iter != end; ++iter)
    {
        if (cur < 0)
        {
            cur = *iter;
        }
        else
        {
            cur += *iter;
        }
        if (sum < cur || iter == begin)
        {
            sum = cur;
        }
    }
    return sum;
}


int main()
{
    // vector<int> maxinum_subarray
    std::vector<int> vec{1, -2, 3, 10, -4, 7, 2, -5};
    std::cout << vec << std::endl;
    int sum = maxinum_subarray(vec.begin(), vec.end());
    std::cout << sum << std::endl;

    // int* maxinum_subarray
    int arr[] = {-2, -8, -1, -5, -9};
    const size_t length = sizeof(arr) / sizeof(int);
    for (size_t i = 0; i < length; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    sum = maxinum_subarray(arr, arr + length);
    std::cout << sum << std::endl;

    // list<int> maxinum_subarray
    std::list<int> lists{2, 8, 1, 5, 9};
    std::cout << lists << std::endl;
    sum = maxinum_subarray(lists.begin(), lists.end());
    std::cout << sum << std::endl;

    return 0;
}

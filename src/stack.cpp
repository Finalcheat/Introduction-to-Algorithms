#include <iostream>
#include <vector>
#include <random>


template <typename T>
class Stack
{
    public:
        Stack() {}

    public:
        bool empty() { return _vec.empty(); }
        void push(const T& v);
        T pop();

    private:
        std::vector<T> _vec;
};


template <typename T>
void Stack<T>::push(const T& v)
{
    _vec.push_back(v);
}

template <typename T>
T Stack<T>::pop()
{
    if (_vec.empty())
        throw std::runtime_error("Stack<T> empty");

    T v = _vec[_vec.size() - 1];
    _vec.pop_back();
    return v;
}


int main()
{
    std::default_random_engine random(time(0));
    std::uniform_int_distribution<int> dis(1, 100);
    const size_t num = 5;
    Stack<int> s;
    for (size_t i = 0; i < num; ++i)
    {
        const int v = dis(random);
        std::cout << v << " ";

        s.push(v);
    }
    std::cout << std::endl;

    for (size_t i = 0; i < num; ++i)
    {
        std::cout << s.pop() << " ";
    }
    std::cout << std::endl;

    return 0;
}

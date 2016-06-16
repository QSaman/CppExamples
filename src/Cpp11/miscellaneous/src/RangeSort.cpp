#include <iostream>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <iterator>

template<typename T>
using IteratorType = typename T::iterator;

template<typename T>
using IteratorCategory = typename std::iterator_traits<T>::iterator_category;

template<typename T>
void sortHelper(T begin, T end, std::random_access_iterator_tag)
{
    std::cout << "random access sort" << std::endl;
    std::sort(begin, end);
}

template<typename T>
void sortHelper(T begin, T end, std::forward_iterator_tag)
{
    std::cout << "forward access sort" << std::endl;
    //decltype(*begin) in this case return int&. As you know, you can't create
    //vector<int&>. There are two methods:
    //1. Use of std::remove_reference
    //2. Use of T::value_type
    //See http://stackoverflow.com/questions/21481466/iterator-category-and-decltype
    using ValueType = typename std::remove_reference<decltype(*begin)>::type;
    std::vector<ValueType> v{begin, end};
    //std::vector<typename T::value_type> v{begin, end};
    std::sort(v.begin(), v.end());
    std::copy(v.begin(), v.end(), begin);
}

template<typename T>
void sort(T& container)
{
    using Iter = IteratorType<T>;
    //"tag dispatch" technique
    sortHelper(container.begin(),
         container.end(),
         IteratorCategory<Iter>{});
}

template<typename T>
void print(T container)
{
    using namespace std;
    for (const auto& val : container)
        cout << val << ' ';
    cout << endl;
}

int main()
{
    std::vector<int> v {4, 2, 3, 1};
    sort(v);
    print(v);
    std::forward_list<int> fl {4, 2, 3, 1};
    sort(fl);
    print(fl);
}

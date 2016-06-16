#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename C>
using ElementType = typename C::value_type;

//See also Vector1.cpp
template<typename Container>
ElementType<Container> sum(Container& c)
{
    ElementType<Container> ret = 0;
    for (const auto& val : c)
        ret += val;
    return ret;
}

template<typename Container>
typename Container::value_type sum2(Container& c)
{
    typename Container::value_type ret = 0;
    for (const auto& val : c)
        ret += val;
    return ret;
}

int main()
{
    //ElementType<vector<int>> is actually an int
    ElementType<vector<int>> a = 7;
    cout << a << endl;

    //ElementType<vector<string>> is actually a string
    ElementType<vector<string>> str = "saman";
    cout << str << endl;

    vector<int> v1 {1, 2, 3};
    cout << sum(v1) << endl;
    cout << sum2(v1) << endl;
}

#include <iostream>
#include <future>
#include <algorithm>
#include <vector>
#include <numeric>

using vt = std::vector<int>::iterator;

int accumulate(vt begin, vt end, int init)
{
    return std::accumulate(begin, end, init);
}

int quickAccumulate(std::vector<int>& v)
{
    if (v.size() < 50)
        return accumulate(v.begin(), v.end(), 0);
    auto size = v.size();
    auto b = v.begin();
    //It's up to std::async that how many threads should do the tasks
    auto f1 = std::async(accumulate,
                         b,
                         b + size / 4, 0);
    auto f2 = std::async(accumulate,
                         b + size / 4,
                         b + size / 2, 0);
    auto f3 = std::async(accumulate,
                         b + size / 2,
                         b + 3 * size / 4, 0);
    std::future<int> f4 = std::async(accumulate,
                                     b + 3 * size / 4,
                                     b + size, 0);
    return (f1.get() + f2.get() + f3.get() + f4.get());
}

int main()
{
    using namespace std;
    vector<int> v1 {1, 2, 3, 4, 5, 6};
    cout << quickAccumulate(v1) << endl;
    vector<int> v2(100);
    for (int i = 0; i < v2.size(); ++i)
        v2[i] = i + 1;
    cout << quickAccumulate(v2) << endl;
}

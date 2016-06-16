#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class LessThan
{
public:
    LessThan(T val) : val{val}
    {

    }

    bool operator()(const T& left)
    {
        return left < val;
    }

private:
    T val;
};

template<typename C, typename P>
int count(C c, P predicate)
{
    int ret = 0;
    for (auto v : c)
        if (predicate(v))
            ++ret;
    return ret;
}

template<typename C, typename V>
void print(C c, V v)
{
    cout << "members which are less than " << v << " in {";
    for (const auto& v : c)
        cout << v << ' ';
    cout << "}: " << count(c, LessThan<V>{v}) << endl;
}

int main()
{
    vector<int> vi1{1, 2, 3};
    print(vi1, 4);

    vector<double> vd1{2.2, 5.5, 7.7, 15.5};
    print(vd1, 8.0);
    vector<int> vi2{4, 7, 15, 18, 100};
    int v = 10;
    cout << "members which are less than " << v << " in {";
    for (auto& val : vi2)
        cout << val << ' ';
    cout << "}: " << count(vi2, [&](int r){return v > r;}) << endl;
    return 0;
}

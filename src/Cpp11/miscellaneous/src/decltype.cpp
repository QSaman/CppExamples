#include <iostream>

template <typename T1, typename T2>
auto sum(T1 left, T2 right) -> decltype(left + right)
{
    return left + right;
}

int main()
{
    using namespace std;
    double a = 7.1;
    int b = 3;
    cout << sum(a, b) << endl;
    decltype(b) c = 7;
    cout << sum(a, c) << endl;
}

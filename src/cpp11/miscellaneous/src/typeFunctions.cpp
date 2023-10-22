#include <iostream>
#include <limits>

int main()
{
    using namespace std;
    constexpr int intMin = numeric_limits<int>::min();
    constexpr int intMax = numeric_limits<int>::max();
    cout << "int limits: " << intMin << ' ' << intMax << endl;
    //min type function
    constexpr unsigned int uintMin = numeric_limits<unsigned int>::min();
    //max type function
    constexpr unsigned int uintMax = numeric_limits<unsigned int>::max();
    cout << "unsigned int limits: " << uintMin << ' ' << uintMax << endl;
    constexpr int intSize = sizeof(int);
    constexpr int uintSize = sizeof(unsigned int);
    cout << "int size: " << intSize << endl;
    cout << "unsigned int size: " << uintSize << endl;
}

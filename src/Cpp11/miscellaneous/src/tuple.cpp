#include <iostream>
#include <tuple>
#include <string>

using std::cout;
using std::endl;

int main()
{
    auto t = std::make_tuple(1, std::string("saman"), 7.7);
    cout << std::get<0>(t) << ' '
         << std::get<1>(t) << ' '
         << std::get<2>(t) << endl;
}

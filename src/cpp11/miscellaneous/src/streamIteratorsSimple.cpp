#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    copy(istream_iterator<string> {cin},
         istream_iterator<string> {},
         ostream_iterator<string> {cout, "\n"});
}

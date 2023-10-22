#include <string>
#include <iostream>

int main()
{
    using namespace std;
    string str = "سامان";
    cout << str.length() << ": "  << str << endl;
    cout << "In UTF-8: ";
    for (unsigned char ch : str)
        cout << hex << (int) ch << ' ';
    cout << endl;
}

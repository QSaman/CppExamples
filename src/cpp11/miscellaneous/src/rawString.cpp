#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
    string str1 {"\n"};
    cout << "str1: " << str1 << endl;
    //you need to use parentheses
    string str2 {R"(\n)"};
    cout << "str2: " << str2 << endl;
    //saman is a delimiter. See http://en.cppreference.com/w/cpp/language/string_literal
    string str3 {R"saman(\n)saman"};
    cout << "str3: " << str3 << endl;
    string str4 {R"(Saman
Saadi)"};
    cout << "str4: " << str4 << endl;
    string str5 {R"delimiter(")delimiter"};
    cout << "str5: " << str5 << endl;
}

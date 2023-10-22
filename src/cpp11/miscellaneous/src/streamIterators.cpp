#include <iostream>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

void method1()
{
    cout << "Enter some strings. After you've done, press CTRL+D in Nix (method1)" << endl;
    //If you enter "Darth Revan" in one line and then press CTRL+D, the size of array is 2
    //because cin skip whitespaces
    vector<string> buffer{istream_iterator<string>{cin}, istream_iterator<string>{}};
    cout << "You've entered:" << endl;
    ostream_iterator<string> out{cout, "\n"};
    copy(buffer.begin(), buffer.end(), out);
}

void method2()
{
    cout << "Enter some strings. After you've done, press CTRL+D in Nix (method2)" << endl;
    string buffer{istream_iterator<char>{cin}, istream_iterator<char>{}};
    cout << "You've entered: " << buffer << endl;
}

void method3()
{
    cout << "Enter some strings. After you've done, press CTRL+D in Nix (method3)" << endl;
    string buffer = string{istreambuf_iterator<char>{cin}, istreambuf_iterator<char>{}};
    cout << "You've entered:" << endl << buffer << endl;
}

int main()
{
    method3();
}

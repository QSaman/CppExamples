#include <iostream>

using namespace std;

template<typename T>
void printIt(T t)
{
    cout << t << ' ';
}

void print()
{
    cout << endl;
}

template<typename Head, typename... Tail>
void print(Head h, Tail... t)
{
    printIt(h);
    print(t...);
}


int main()
{
    print(1, 1.2, "saman");
    print(1, 5, "saman", 7, "revan", 7.7);
}

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class MyVector : public vector<T>
{
public:
    using vector<T>::vector;
    T& operator[](int i)
    {
        return vector<T>::at(i);
    }

    T& operator[](int i) const
    {
        return vector<T>::at(i);
    }
};

int main()
{
    MyVector<int> v{1, 2, 3};
    for (auto val : v)
        cout << val << ' ';
    cout << endl;
    //below statement raise an out_of_range exception
    try
    {
        cout << v[v.size()] << endl;
    }
    catch(out_of_range)
    {
        cerr << "out_of_range exception has occured!" << endl;
    }
    catch(...)
    {
        cerr << "An unknwn exception has occured!" << endl;
    }
}

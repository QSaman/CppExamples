#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class MyVector : public vector<T>
{
public:
    using size_type = typename vector<T>::size_type;
    using vector<T>::vector;
    T& operator[](size_type i)
    {
        return vector<T>::at(i);
    }

    T& operator[](size_type i) const
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
        cout << v[static_cast<unsigned int>(v.size())] << endl;
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

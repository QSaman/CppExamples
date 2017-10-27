#include <iostream>
#include <memory>
#include <initializer_list>

using namespace std;

template<typename T>
class Vector
{
public:
    using size_type = typename initializer_list<T>::size_type;
    explicit Vector(size_type size) : size{size}
    {
        cout << "conversion constructor" << endl;
        int* aTmp = new int[size];
        for (auto i = 0; i < size; ++i)
            aTmp[i] = i;
        a.reset(aTmp);
    }

    Vector(const Vector<T>&) = delete;
    T& operator=(const Vector<T>&) = delete;

    Vector(initializer_list<T> list) : size{list.size()}
    {
        cout << "initializer list constructor" << endl;
        int i = 0;
        a.reset(new T[size]);
        for (auto iter = list.begin(); iter != list.end(); ++iter, ++i)
            a.get()[i] = *iter;
    }

    Vector(Vector<T>&& v)
    {
        cout << "Move constructor" << endl;
        a.reset(v.a.release());
        size = v.size;

        v.size = 0;
    }

    T& operator=(Vector<T>&& v)
    {
        cout << "Move assignment" << endl;
        a.reset(v.a.release());
        size = v.size;
        v.size = 0;
        return *this;
    }

    T& operator[](const int index)
    {
        return a.get()[index];
    }

    T& operator[](const int index) const
    {
        return a.get()[index];
    }

    T* begin()
    {
        return &(*a);
    }

    T* end()
    {
        return (begin() + size);
    }

    T* begin() const
    {
        return &(*a);
    }

    T* end() const
    {
        return (begin() + size);
    }

private:
    unique_ptr<T> a;
    size_type size;
};

template<typename C>
void print(const C& c)
{
    for (auto v : c)
        cout << v << ' ';
    cout << endl;
}

//See also Aliases.cpp
template<typename C, typename V>
V sum(const C& c, V s)
{
    for (auto v : c)
        s += v;
    return s;
}

Vector<int> vectorFactory()
{
    Vector<int> v{5, 6};
    return v;
}

int main()
{
    Vector<int> vi1(5);
    print(vi1);
    cout << "Sum: " << sum(vi1, 0) << endl;
    Vector<double> vd1 = {1.1, 2.2};
    print(vd1);
    cout << "Sum: " << sum(vd1, 0.0) << endl;
    Vector<int> vi2 = vectorFactory();
    print(vi2);
    cout << "Sum: " << sum(vi2, 0) << endl;
    return 0;
}

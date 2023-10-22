#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Student
{
public:
    Student(string name, string family) : name{name}, family{family}
    {
    }

    //There is no default equality operator for Student
    bool operator==(Student right)
    {
        return family == right.family;
    }

    string name, family;
};

bool operator<(const Student& l, const Student& r)
{
    return l.family < r.family;
}

ostream& operator<<(ostream& out, const Student& student)
{
    return out << '{' << student.name << ", " << student.family << '}';
}

template<typename Container, typename Predicate>
void forAll(const Container& c, Predicate p)
{
    for (auto& v : c)
        p(v);
}

template<typename Container>
using Element = typename Container::value_type;

template<typename Container>
void printAll(const Container& c)
{
    forAll(c, [](Element<Container> e){cout << e << ' ';});
    cout << endl;
}

template<typename Container>
void sort(Container& c)
{
    std::sort(c.begin(), c.end());
}

int main()
{
    vector<Student> v1{{"smana", "saadi"}, {"darth", "revan"}, {"lord", "revan"}};
    cout << "before sort: ";
    printAll(v1);
    sort(v1);
    cout << "after sort: ";
    printAll(v1);
    vector<Student> v2;
    unique_copy(v1.begin(), v1.end(), back_inserter(v2));
    Student s1{"saman", "saadi"};
    cout << "v2: ";
    printAll(v2);
}

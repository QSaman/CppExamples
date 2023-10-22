#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

class Record
{
public:
    Record(const std::string& name) : name {name}
    {

    }
    std::string name;
};

std::ostream& operator<<(std::ostream& out, const Record& r)
{
    out << r.name;
    return out;
}

int main()
{
    using namespace std;
    vector<Record> vr {Record{"malak"},
                       Record{"revan"},
                       Record{"saadi"},
                       Record{"saman"}};

    auto predicate = [](const Record& left, const Record& right) {return left.name < right.name;};
    sort(vr.begin(), vr.end(), predicate);
    auto er = equal_range(vr.begin(), vr.end(), Record{"saman"}, predicate);
    for (auto p = er.first; p != er.second; ++p)
        cout << *p << ' ';
    cout << endl;
}

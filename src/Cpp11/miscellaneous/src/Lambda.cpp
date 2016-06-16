#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

class Saman
{
public:
    explicit Saman(string name) : name{name}
    {

    }
    void whoAmI()
    {
        cout << name << endl;
    }

    void whoAmI(int id)
    {
        cout << name << ' ' << id << endl;
    }

private:
    string name;
};

template<typename Container, typename Operation>
void forAll(Container& c, Operation op)
{
    for (auto val : c)
        op(val);
}

int main()
{
    vector<Saman> vs {Saman("saman"), Saman("revan"), Saman("galen")};
    forAll(vs, [](Saman& saman){saman.whoAmI();});
    cout << endl;
    int id = 7;
    //All external variables are captured by reference
    forAll(vs, [&](Saman& saman){saman.whoAmI(id);});
    cout << endl;
    //only id will be captured (by reference)
    forAll(vs, [&id](Saman& saman){saman.whoAmI(id);});
    cout << endl;
    //All external variables are captured by value
    forAll(vs, [=](Saman& saman){saman.whoAmI(id);});
    cout << endl;
    //Only id will be captured (by value)
    forAll(vs, [id](Saman& saman){saman.whoAmI(id);});
    cout << endl;
}

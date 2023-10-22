#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    map<string, int> m {{"saman", 1},
                       {"revan", 2},
                       {"malak", 3}};
    auto i = find_if(m.begin(), m.end(), [](const pair<string, int>& r){return r.second >= 2;});
    cout << i->first << endl;
    auto cnt = count_if(m.begin(), m.end(), [](const pair<string, int>& r){return r.second >= 2;});
    cout << cnt << endl;
}

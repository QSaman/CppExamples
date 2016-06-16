//A simple copy program using istreambuf_iterator
//For more information:
//http://stackoverflow.com/questions/4761529/efficient-way-of-reading-a-file-into-an-stdvectorchar/4761779

#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>

using namespace std;

string from, to;

bool parseInput(int argc, char* argv[])
{
    if (argc == 1)
    {
        from = "from";
        to = "to";
    }
    else if (argc == 3)
    {
        from = argv[1];
        to = argv[2];
    }
    else
    {
        cerr << "You must provide two arguments or nothing" << endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (!parseInput(argc, argv))
        return 1;
    ifstream fin{from, std::ios::binary};
    ofstream fout{to, std::ios::binary};
    copy(istreambuf_iterator<char>{fin},
         istreambuf_iterator<char>{},
         ostream_iterator<char>{fout});
}

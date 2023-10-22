#include <iostream>
#include <thread>

using namespace std;

int main()
{
    auto t0 = chrono::high_resolution_clock::now();
    this_thread::sleep_for(chrono::milliseconds{20});
    auto t1 = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << endl;
}

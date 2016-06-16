#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    using namespace std;
    auto t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
        this_thread::sleep_for(chrono::milliseconds{10});
    chrono::high_resolution_clock::time_point t1 =
            chrono::high_resolution_clock::now();
    chrono::milliseconds diff =
            chrono::duration_cast<chrono::milliseconds>(t1 - t0);
    cout << diff.count() << "ms" << endl;
}

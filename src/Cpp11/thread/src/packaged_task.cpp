#include <iostream>
#include <future>
#include <algorithm>
#include <thread>

int accumulate(int* first, int* end, int init)
{
    return std::accumulate(first, end, init);
}

int main()
{
    using TaskType = int(int*, int*, int);
    std::packaged_task<TaskType> pt0 {accumulate};
    std::packaged_task<TaskType> pt1 {accumulate};
    std::future<int> f0 = pt0.get_future();
    std::future<int> f1 = pt1.get_future();
    int a[] = {1, 2, 3, 4, 5, 6};
    std::thread t0 {move(pt0), a, a + 3, 0};
    std::thread t1 {move(pt1), a + 3, a + 6, 0};
    {
        using namespace std;
        cout << f0.get() + f1.get() << endl;
    }
    t0.join();
    t1.join();
}

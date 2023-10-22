#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

static mutex m1, m2, m3;

void deadlock(int id)
{
    if (id == 1)
    {
        unique_lock<mutex> l1{m1};
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> l2{m2};
        unique_lock<mutex> l3{m3};
        cout << "I am " << id << " and I've sucessfully acuired all three locks!" << endl;
    }
    else if (id == 2)
    {
        unique_lock<mutex> l2{m2};
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> l3{m3};
        unique_lock<mutex> l1{m1};
        cout << "I am " << id << " and I've sucessfully acuired all three locks!" << endl;
    }
    else if (id == 3)
    {
        unique_lock<mutex> l3{m3};
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> l1{m1};
        unique_lock<mutex> l2{m2};
        cout << "I am " << id << " and I've sucessfully acuired all three locks!" << endl;
    }
}

void noDeadlock(int id)
{
    if (id == 1)
    {
        unique_lock<mutex> l1{m1, defer_lock};
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> l2{m2, defer_lock};
        unique_lock<mutex> l3{m3, defer_lock};
        lock(l1, l2, l3);
        cout << "I am " << id << " and I've sucessfully acuired all three locks!" << endl;
    }
    else if (id == 2)
    {
        unique_lock<mutex> l2{m2, defer_lock};
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> l3{m3, defer_lock};
        unique_lock<mutex> l1{m1, defer_lock};
        lock(l2, l3, l1);
        cout << "I am " << id << " and I've sucessfully acuired all three locks!" << endl;
    }
    else if (id == 3)
    {
        unique_lock<mutex> l3{m3, defer_lock};
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> l1{m1, defer_lock};
        unique_lock<mutex> l2{m2, defer_lock};
        lock(l3, l1, l2);
        cout << "I am " << id << " and I've sucessfully acuired all three locks!" << endl;
    }
}

int main()
{
    thread::id id = this_thread::get_id();
    cout << "main thread id: " << id << endl;

    thread t1{noDeadlock, 1};
    thread t2{noDeadlock, 2};
    thread t3{noDeadlock, 3};
    t1.join();
    t2.join();
    t3.join();
}

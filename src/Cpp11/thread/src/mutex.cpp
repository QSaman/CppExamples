#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

static mutex m;

void f(int id)
{
    m.lock();
    cout << "I am " << id << " and I'm in critical section" << endl;
    m.unlock();
}

void g(int id)
{
    unique_lock<mutex> lock{m}; //In unique_lock constructor we have m.lock()
    cout << "I am " << id << " and I'm in critical section" << endl;
}   //In unique_lock destructor we have m.unlock();

void h(int id)
{
    {
        unique_lock<mutex> lock{m};
        cout << "I am " << id << " and I'm in critical section" << endl;
    }
    cout << "I am " << id << " and I'm not in critical section" << endl;
}

void h1(int id)
{
    {
        lock_guard<mutex> lock{m};
        cout << "I am " << id << " and I'm in critical section (lock_guard)" << endl;
    }
    cout << "I am " << id << " and I'm not in critical section" << endl;
}

int main()
{
    thread t1{f, 1};
    thread t2{f, 2};
    t1.join();
    t2.join();
    thread t3{g, 3};
    thread t4{g, 4};
    t3.join();
    t4.join();
    thread t5{h, 5};
    thread t6{h, 6};
    t5.join();
    t6.join();
    thread t7{h1, 7};
    thread t8{h1, 8};
    t7.join();
    t8.join();
    std::mutex m_test;
    m_test.lock();
    //If you uncomment the following line, it's a deadlock! In other words you cannot see "Hello World!"
    //m_test.lock();
    std::cout << "Hello There!" << std::endl;
}

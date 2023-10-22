#include <iostream>
#include <thread>
#include <future>
#include <exception>
#include <functional> //std::ref

using namespace std;


//Note that future<char> is passed by value
void print(string name, int index, future<char> f)
{
    try
    {
        cout << "name[" << index << "]: " << f.get() << endl;
    }
    catch(exception& ex)
    {
        cerr << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "unknown exception" << endl;
    }
}

//Note that future<char> is passed by reference
void print2(string name, int index, future<char>& f)
{
    try
    {
        cout << "name[" << index << "]: " << f.get() << endl;
    }
    catch(exception& ex)
    {
        cerr << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "unknown exception" << endl;
    }
}

int main()
{
    promise<char> p1, p2;
    future<char> f1 = p1.get_future(),
                f2 = p2.get_future();
    string str {"saman"};
    //future class doesn't have a copy constructor, so we should use move
    thread t1 {print, str, 0, move(f1)};
    thread t2 {print, str, 7, move(f2)};
    cout << "main thread goes to sleep for 3s..." << endl;
    this_thread::sleep_for(chrono::seconds{3});

    p1.set_value(str.at(0));
    try
    {
        p2.set_value(str.at(7));
    }
    catch(...)
    {
        p2.set_exception(current_exception());
    }
    t1.join();
    t2.join();
    promise<char> p3;
    future<char> f3 = p3.get_future();
    str = "revan";
    //For pass f3 by reference we should use std::ref
    thread t3{print2, str, 0, ref(f3)};
    p3.set_value(str[0]);
    t3.join();
}

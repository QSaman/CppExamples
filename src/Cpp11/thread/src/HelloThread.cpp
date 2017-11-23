//You need to enable threading support:
//In CMake add find_package(Threads REQUIRED)
//In qmake add CONFIG += c++11 thread
//In GCC compile with: g++ -std=c++11 -pthread thread.cpp

#include <iostream>
#include <thread>
#include <string>

void f1()
{
    std::cout << std::this_thread::get_id() << " (f1): Hello World!" << std::endl;
}

void f2(const std::string& str)
{
    std::cout << std::this_thread::get_id() << " (f2): " << str << std::endl;
}

class Task
{
public:
    void operator()()
    {
        std::cout << std::this_thread::get_id() << " (Task): Hello World!" << std::endl;
    }
    void method()
    {
        std::cout << std::this_thread::get_id() << " (Task method): Hello World!" << std::endl;
    }
};

int main()
{
    std::thread t1([]()
    {
        std::cout << std::this_thread::get_id() << " (lambda): Hello World!" << std::endl;
    });
    std::thread t2(f1);
    std::thread t3(f2, "Hello World!");
    std::thread t4 {Task()};
    Task task2;
    //https://stackoverflow.com/questions/10673585/start-thread-with-member-function:
    //Since we send a pointer to a function pointer, the thread class runs it as task2.method()
    std::thread t5(&Task::method, std::ref(task2));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

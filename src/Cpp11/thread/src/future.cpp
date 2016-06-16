#include <future>
#include <thread>
#include <iostream>
#include <string>

int main()
{
    std::promise<std::string> promise;
    std::thread producer([&]
    {
        promise.set_value("Hello World!");
    });
    auto future = promise.get_future();
    std::thread consumer([&]
    {
        std::cout << future.get() << std::endl;
    });
    producer.join();
    consumer.join();
}

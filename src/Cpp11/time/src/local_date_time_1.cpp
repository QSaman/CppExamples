//http://en.cppreference.com/w/cpp/chrono/c/localtime

#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h> // defines putenv in POSIX
 
int main()
{
    std::time_t t = std::time(nullptr);
    std::cout << "UTC:       " << std::put_time(std::gmtime(&t), "%c %Z") << '\n';
    std::cout << "local:     " << std::put_time(std::localtime(&t), "%c %Z") << '\n';
    // POSIX-specific:
    std::string tz = "TZ=Asia/Singapore";
    putenv(tz.data());
    std::cout << "Singapore: " << std::put_time(std::localtime(&t), "%c %Z") << '\n';
}

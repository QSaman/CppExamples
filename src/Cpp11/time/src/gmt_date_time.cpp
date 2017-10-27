//http://en.cppreference.com/w/cpp/chrono/c/strftime
//https://stackoverflow.com/questions/20619236/how-to-get-utc-time


#include <ctime>
#include <iostream>
#include <locale>
 
int main()
{
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::gmtime(&t))) {
        std::cout << mbstr << '\n';
    }
}

 

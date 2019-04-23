// You shouldn't compile this file. Because of that its extension is not cpp

#include "print_all.h"

#include <iostream>
#include <utility>
 
template<typename T, typename... Args>
void print_all(T arg, Args&&... args)
{
	std::cout << arg << ' ';
        print_all(args...);
}

void print_all()
{
	std::cout << std::endl;
}

int sum(const int a, const int b)
{
    return a + b;
}

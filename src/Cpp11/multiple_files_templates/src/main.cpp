#include "print_all.h"

#include <string>

int main()
{
    const std::string foo = "foo";
    print_all(2, 3, foo, sum(2, 3));
}

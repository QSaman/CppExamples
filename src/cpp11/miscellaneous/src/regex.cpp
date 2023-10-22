#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
    //The default syntax for regex is ECMAScript
    //See http://www.cplusplus.com/reference/regex/ECMAScript/

    //Below pattern:
    //start with two letters \w{2}
    //optionally followed by some spaces \s*
    //followed by five digits \d{5}
    //optionally followed by a dash and four digits -\d{4}
    std::regex pattern(R"(\w{2}\s*\d{5}(-\d{4}})?)");
}

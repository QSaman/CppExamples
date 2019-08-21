#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <cassert>

inline bool isInteger(std::string str_number, int64_t& integralPart)
{
	auto len = str_number.length();
	std::size_t first = 0, last = len - 1;

	for (; std::isspace(str_number[first]) && first < len; ++first);
	for (; std::isspace(str_number[last]) && last > 0; --last);

	if (first > last)
		return false;

	std::istringstream iss(str_number.substr(first, last - first + 1));

	int64_t fraction;
	char ch;

	//isInteger returns ture for these examples:
	//7
	//7.
	//7.00
	return iss >> integralPart && (iss.eof() || str_number[last] == '.' || (iss >> ch && ch == '.' && iss >> fraction && fraction == 0 && iss.eof()));
}

int main()
{
	int64_t number;

	(isInteger("7", number) == true);
	assert(isInteger("7.", number) == true);
	assert(isInteger("7.00", number) == true);
	
	assert(isInteger(" 7. ", number) == true);
	assert(isInteger("7.12", number) == false);

}

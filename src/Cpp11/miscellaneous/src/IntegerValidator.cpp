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
	char next;

	if ((first + 1) < len && str_number[first] == '.' && std::isdigit(str_number[first + 1]))	// For handling .0
		integralPart = 0;
	else if ((first + 2) < len && (str_number[first] == '+' || str_number[first] == '-') && 	// For handling +.0 or -.0
	         str_number[first + 1] == '.' && std::isdigit(str_number[first + 2]))
	{
		integralPart = 0;
		iss >> ch;	//Discaring + or -
	}
	else if (!(iss >> integralPart))
		return false;

	//isInteger returns ture for these examples:
	//7
	//7.
	//7.00
	return iss.eof() ||	//For cases like 7	        
		   (iss >> ch && ch == '.' && ((next = iss.peek()) == EOF || // For cases like 7.
		   (std::isdigit(next) && iss >> fraction && fraction == 0 && iss.eof()))); // For handling 7.00. Note 7.+00 is invalid!
}

int main()
{
	int64_t number;

	assert(isInteger("7", number) == true);
	assert(isInteger("   +7     ", number) == true);
	assert(isInteger("7.", number) == true);
	assert(isInteger("7.00", number) == true);
	
	assert(isInteger(" 7. ", number) == true);
	assert(isInteger("7.12", number) == false);
	assert(isInteger(".", number) == false);

	assert(isInteger(".0", number) == true);
	assert(isInteger("+.0", number) == true);
	assert(isInteger("-.0", number) == true);

	assert(isInteger("7.+0", number) == false);

	assert(isInteger("abc", number) == false);
	assert(isInteger("123abc", number) == false);
	assert(isInteger("123 456", number) == false);

	assert(isInteger("7.0000000000000000000000000000000000000000000000000000000000001", number) == false);
}

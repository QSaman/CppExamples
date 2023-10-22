// Substitution Failure Is Not An Error (SFINAE)
// https://en.cppreference.com/w/cpp/language/sfinae
// Please refer to cpp14 and cpp17 versions

#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>

template <typename Integer, typename std::enable_if<std::is_integral<Integer>::value, bool>::type = true>
bool areEqual(Integer t1, Integer t2)
{
	return t1 == t2;
}

template <typename Floating, typename std::enable_if<std::is_floating_point<Floating>::value, bool>::type = true>
bool areEqual(Floating t1, Floating t2)
{
	return fabs(t1 - t2) <= 1e-2;
}

int main()
{
	assert(areEqual(1, 1));
	assert(areEqual(1.2, 1.2));

	assert(!areEqual(1, 2));
	assert(!areEqual(1.1, 1.2));
}

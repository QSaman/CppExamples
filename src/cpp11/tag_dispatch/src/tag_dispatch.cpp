// Substitution Failure Is Not An Error (SFINAE)
// https://en.cppreference.com/w/cpp/language/sfinae
// Please refer to cpp14 and cpp17 versions

#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>

namespace implementation_details
{
template <typename Integer>
bool areEqual(Integer i1, Integer i2, std::true_type)
{
	return i1 == i2;
}

template <typename Floating>
bool areEqual(Floating f1, Floating f2, std::false_type)
{
	return fabs(f1 - f2) <= 1e-2;
}
}

template <typename Number>
bool areEqual(Number n1, Number n2)
{
	constexpr std::is_integral<Number> is_Integral;
	return implementation_details::areEqual(n1, n2, is_Integral);
}

int main()
{
	assert(areEqual(1, 1));
	assert(areEqual(1.2, 1.2));

	assert(!areEqual(1, 2));
	assert(!areEqual(1.1, 1.2));
}

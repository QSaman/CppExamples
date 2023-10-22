// Substitution Failure Is Not An Error (SFINAE)
// https://en.cppreference.com/w/cpp/language/sfinae
// Please refer to cpp11 and cpp17 versions

#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>

template <typename Integer, typename std::enable_if_t<std::is_integral_v<Integer>, bool> = true>
bool areEqual(Integer t1, Integer t2)
{
	return t1 == t2;
}

template <typename Floating, typename std::enable_if_t<std::is_floating_point_v<Floating>, bool> = true>
bool areEqual(Floating t1, Floating t2)
{
	return fabs(t1 - t2) <= 1e-2;
}

template<typename Number>
bool areEqual2(Number n1, Number n2)
{
	if constexpr (std::is_integral_v<Number>)
	{
		return n1 == n2;
	}
	else if (std::is_floating_point_v<Number>)
	{
		return fabs(n1 - n2) <= 1e-2;
	}
	else
	{
		return false;
	}
}

int main()
{
	assert(areEqual(1, 1));
	assert(areEqual2(1, 1));

	assert(areEqual(1.2, 1.2));
	assert(areEqual2(1.2, 1.2));

	assert(!areEqual(1, 2));
	assert(!areEqual2(1, 2));

	assert(!areEqual(1.1, 1.2));
	assert(!areEqual2(1.1, 1.2));
}

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <type_traits>

namespace implementation_details
{
template <typename T, bool B>
struct Tag
{
};

template <typename Integer>
bool areEqual(Integer i1, Integer i2, Tag<std::is_integral<Integer>, true>)
{
	return i1 == i2;
}

template <typename Floating>
bool areEqual(Floating f1, Floating f2, Tag<std::is_floating_point<Floating>, true>)
{
	return fabs(f1 - f2) <= 1e-2;
}
}

template <typename Number>
bool areEqual(Number n1, Number n2)
{
	using implementation_details::Tag;

	using FinalTag = typename std::conditional<std::is_integral<Number>::value,
		Tag<std::is_integral<Number>, std::is_integral<Number>::value>,
	Tag<std::is_floating_point<Number>, std::is_floating_point<Number>::value>>::type;

	FinalTag tag;
	return implementation_details::areEqual(n1, n2, tag);
}

int main()
{
	assert(areEqual(1, 1));
	assert(areEqual(1.2, 1.2));

	assert(!areEqual(1, 2));
	assert(!areEqual(1.1, 1.2));

	// compile error:
	// areEqual(std::string("1"), std::string("1")); 
}

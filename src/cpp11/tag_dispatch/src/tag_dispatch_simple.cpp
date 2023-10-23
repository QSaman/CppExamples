#include <cassert>
#include <iostream>
#include <type_traits>

namespace implementation_details
{
template <typename Arithmetic>
Arithmetic multiply(Arithmetic a1, Arithmetic a2, std::true_type)
{
	return a1 * a2;
}
}

template <typename Type>
Type multiply(Type t1, Type t2)
{
	return implementation_details::multiply(t1, t2, std::is_arithmetic<Type>());
}

int main()
{
	assert(multiply(2, 3) == 6);
	assert(multiply(2.00, 3.00) == 6.00);
}

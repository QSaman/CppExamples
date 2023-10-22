#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template<typename Type>
std::size_t length(Type t)
{
	if constexpr (std::is_arithmetic_v<Type>)
	{
		return length(std::to_string(t));
	}
	else if constexpr (std::is_member_pointer_v<decltype(&Type::size)>)
	{
		return t.size();
	}
	else if constexpr (std::is_member_pointer_v<decltype(&Type::length)>)
	{
		return t.length();
	}
	else
	{
		return 0;
	}
}

int main()
{
	assert(length(1234) == 4);

	const std::string str("foo");
	assert(length(str) == 3);

	const std::vector<int> v {1, 2, 3, 4, 5};
	assert(length(v) == 5);
}

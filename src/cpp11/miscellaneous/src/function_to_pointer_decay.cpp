#include <iostream>
#include <cassert>

void myFunc(int, char) {}

const void* myFuncAddress = reinterpret_cast<const void*>(&myFunc);

template<typename MyFunc>
void f1(MyFunc func)
{
	const void* funcAddress = reinterpret_cast<const void*>(&func);
	assert(myFuncAddress != funcAddress);	//func is decying to pointer. The type of func is void(*)(int, char)
}

template<typename MyFunc>
void f2(MyFunc& func)
{
	const void* funcAddress = reinterpret_cast<const void*>(&func);
	assert(myFuncAddress == funcAddress);	//The type of func is void(&)(int, char)
}

int main()
{
	f1(myFunc);
	f2(myFunc);
}

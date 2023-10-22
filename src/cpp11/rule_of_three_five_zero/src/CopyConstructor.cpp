#include <iostream>
#include <cassert>

struct Test
{
	Test(int a1_, int a2_) : a1{a1_}, a2{a2_}, ref{a1}
	{
		std::cout << "Inside Test(int a1_, int a2_)" << std::endl;
	}

	int a1, a2;
	const int& ref;
};

struct Test2
{
	Test2(int a1_, int a2_) : a1{a1_}, a2{a2_}, ref{a1}
	{
		std::cout << "Inside Test2(int a1_, int a2_)" << std::endl;
	}

	Test2(const Test2& t) : a1{t.a1}, a2{t.a2}, ref{a1}
	{
		std::cout << "Inside Test2(const Test& t)" << std::endl;
	}

	int a1, a2;
	int& ref;
};

int main()
{
	Test t1(1, 2);
	Test t2(t1); //Default copy constructor. Since there is Lvalue reference, the default constructor is dangerous
	assert(&t1.ref == &t2.ref);

	Test2 t3{3, 4};
	Test2 t4{t3};
	assert(&t3.ref != &t4.ref);
}

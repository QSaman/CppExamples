// Curiously recurring template pattern (CRTP):
// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
// Please refer to cpp11 and cpp14 versions too

#include <iostream>
#include <type_traits>
#include <utility>

template <typename Derived>
struct Base
{
	void templateMethod()
	{
		std::cout << "Inside Base::templateMethod" << std::endl;
		std::cout << "Before executing Base::doIt" << std::endl;
		doIt();
		std::cout << "After executing Base::doIt" << std::endl;
	}
protected:
	void  doIt()
	{
		// Base should be a friend of D1 so It can access Derived::doIt
		if constexpr (!std::is_same_v<decltype(&Derived::doIt), decltype(&Base::doIt)>)
		{
			static_cast<Derived*>(this)->doIt();
		}
		else
		{
			std::cout << "Base::doIt" << std::endl;
		}
	}
};

struct D1 : Base<D1>
{
protected:
	void doIt()
	{
		std::cout << "D1::doIt" << std::endl;
	}

	template <typename>
	friend struct Base;
};

struct D2 : Base<D2>
{
};

int main()
{
	D1 d1;
	D2 d2;

	d1.templateMethod();	//D1::doIt
	d2.templateMethod();	//Base:doIt
}

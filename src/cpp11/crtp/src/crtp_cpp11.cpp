// Curiously recurring template pattern (CRTP):
// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
// Please refer to cpp14 and cpp17 versions too

#include <iostream>
#include <type_traits>

template <typename Derived, bool derivedHasDoIt>
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
	// https://en.cppreference.com/w/cpp/language/sfinae
	template <bool derivedHasIt = derivedHasDoIt>
	typename std::enable_if<derivedHasIt>::type  doIt()
	{
		// Base should be a friend of D1 to call D1::doIt
		static_cast<Derived*>(this)->doIt();
	}

	// https://en.cppreference.com/w/cpp/language/sfinae
	template <bool derivedHasIt = derivedHasDoIt>
	typename std::enable_if<!derivedHasIt>::type  doIt()
	{
		std::cout << "Base::doIt" << std::endl;
		static_assert(!derivedHasDoIt, "Base::doIt is called unexpectedly!");
	}
};

struct D1 : Base<D1, true>
{
protected:
	void doIt()
	{
		std::cout << "D1::doIt" << std::endl;
	}

	template <typename, bool>
	friend struct Base;
};

struct D2 : Base<D2, false>
{
};

int main()
{
	D1 d1;
	D2 d2;

	d1.templateMethod();	//D1::doIt
	d2.templateMethod();	//Base:doIt
}

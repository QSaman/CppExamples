#include <iostream>
#include <cassert>

template<typename Array>
void f1(Array array)
{
	assert(sizeof(array) == sizeof(const char*));	//The type of array is const char*
}

template<typename Array>
void f2(Array& array)
{
	assert(sizeof(array) == 6 * sizeof(char));	//the type of array is const char(&)[6]. We can have a reference to an array!
}

template<typename Array, std::size_t size>
constexpr std::size_t arraySize(Array(&)[size]) noexcept	//Note Array&[size] means an array to references which is syntax error!
{
	return size;
}

int main()
{
	const char strArray[6] = "saman";
	const char* strPtr = strArray;	//Because of array-to-pointer decay, we can convert from const char[6] to const char*
	assert(sizeof(strArray) == 6 * sizeof(char));
	assert(sizeof(strPtr) == sizeof(const char*));

	const void* strArrayAddress = &strArray;
	const void* strArray1stElementAddress = &strArray[0];
	assert(strArrayAddress == strArray1stElementAddress);

	const void* strPtrAddress = &strPtr;
	const void* strPtr1stElementAddress = &strPtr[0];
	assert(strPtrAddress != strArrayAddress);
	assert(strPtr1stElementAddress == strArrayAddress);

	f1(strArray);
	f2(strArray);
	assert(arraySize(strArray) == 6);
}

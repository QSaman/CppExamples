#include <iostream>

class C
{
public:
    C(int n, double d) : n{n}, d{d} {}
    operator int() {return n;}  //implicit conversion
    explicit operator double() {return d;}  //explicit conversion
private:
    int n;
    double d;
};

void fInt(int n)
{
    std::cout << n << std::endl;
}

void fDouble(double d)
{
    std::cout << d << std::endl;
}

int main()
{
    C c(7, 7.7);
    fInt(c);    //7
    fDouble(c); //7
    fDouble((double)c); //7.7
}
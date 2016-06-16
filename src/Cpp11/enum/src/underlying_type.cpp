#include <iostream>
enum class COLOR
{
    Blue,
    Red,
    Green,
    Purple,
    First=Blue,
    Last=Purple
};

inline COLOR operator++( COLOR& x ) { return x = (COLOR)(std::underlying_type<COLOR>::type(x) + 1); }
COLOR operator*(COLOR c) {return c;} 
COLOR begin(COLOR r) {return COLOR::First;}
COLOR end(COLOR r)   {COLOR l=COLOR::Last; return ++l;}

std::ostream& operator<<(std::ostream& o, COLOR x) {
	return o << std::underlying_type<COLOR>::type(x);
}


int main() { 
    for(auto c : COLOR()) {
        std::cout << c << '\n';
    }
    return 0;
}
#include <iostream>
#include <chrono>

using Clock = std::chrono::steady_clock;	//For duration using steady_clock is recommended. For more information: https://en.cppreference.com/w/cpp/chrono/high_resolution_clock
using HighResClock = std::chrono::high_resolution_clock;
using SystemClock = std::chrono::system_clock;

int main()
{
	std::cout << "Clock tick period is " << Clock::period::num << '/' << Clock::period::den << " seconds" << std::endl;
	std::cout << "High resolution clock tick period is " << HighResClock::period::num << '/' << HighResClock::period::den << " seconds" << std::endl;
	std::cout << "System clock tick period is " << SystemClock::period::num << '/' << SystemClock::period::den << " seconds" << std::endl;

	auto timePoint = Clock::now();
	auto timePointDuration = timePoint.time_since_epoch();
	std::chrono::time_point<Clock, std::chrono::nanoseconds> timePoint_ns(timePoint);

	std::cout << "Time since steady_clock epoch: " << timePointDuration.count() << " possibly nano seconds" << std::endl;
	std::cout << "Time since steady_clock epoch: " << timePoint_ns.time_since_epoch().count() << " nano seconds" << std::endl;

	using Hour = std::chrono::duration<long double, std::ratio<60 * 60>>;
	Hour hoursSinceEpoch(timePointDuration);

	std::cout << "Hours since steady_clock epoch: " << hoursSinceEpoch.count() << std::endl;	//In my case 2.07829 hours (possibly epoch is boot time of operating system)

	using std::chrono::hours;

	hours h = std::chrono::duration_cast<hours>(timePointDuration);
	std::cout << "Hours since steady_clock epoch: " << std::fixed << h.count() << std::endl; // In my case 2 

	using Milliseconds = std::chrono::duration<long double, std::ratio<1, 1000>>;

	Milliseconds ms(timePointDuration);
	std::cout << "Millisecons since steady_clock epoch: " << std::fixed << ms.count() << std::endl;

	using std::chrono::microseconds;

	microseconds micro = std::chrono::duration_cast<microseconds>(timePointDuration); //microseconds micro(timePointDuration) is syntax error
	std::cout << "Microseconds since steady_clock epoch: " << std::fixed << micro.count() << std::endl;

}

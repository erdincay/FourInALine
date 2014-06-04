#include "Timer.h"

namespace solution
{
	using namespace std;
	using namespace std::chrono;

	Timer::Timer(long period)
		:t_start_(high_resolution_clock::now()),
		period_(period)
	{
	}
	
	Timer::~Timer()
	{
	}

	long Timer::getPeriod()
	{
		return duration_cast<milliseconds>(high_resolution_clock::now() - t_start_).count();
	}

	string Timer::getPeriodUnit()
	{
		return "milliseconds";
	}

	bool Timer::TimeOver()
	{
		return getPeriod() > period_;
	}

}

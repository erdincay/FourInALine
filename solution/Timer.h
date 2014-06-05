#pragma once
#include <chrono>
#include <string>

namespace solution
{
	class Timer
	{
	public:
		Timer(long long period);
		~Timer();

		std::string getPeriodUnit();
		bool TimeOver();

	protected:
		long long getPeriod();

	private:
		std::chrono::high_resolution_clock::time_point t_start_;
		long long period_;
	};

}


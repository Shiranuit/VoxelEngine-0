#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	timestart = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
}

void Timer::reset() 
{
	timestart = std::chrono::high_resolution_clock::now();
}

long long Timer::getEllapsedMicroSeconds()
{
	std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(now - timestart).count();
}
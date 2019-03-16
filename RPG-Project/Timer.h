#pragma once
#include <iomanip>
#include <iostream>
#include <chrono>
class Timer
{
public:
	Timer();
	virtual ~Timer();
	void reset();
	long long getEllapsedMicroSeconds();
private:
	std::chrono::steady_clock::time_point timestart;
};


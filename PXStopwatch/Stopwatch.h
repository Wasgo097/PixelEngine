#pragma once
#include <chrono>
class Stopwatch {
public:
	Stopwatch();
	void Reset();
	std::uint64_t Elapsed();
private:
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_pt;
	time_pt start_time;
};
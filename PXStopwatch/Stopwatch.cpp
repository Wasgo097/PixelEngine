#include "pch.h"
#include "Stopwatch.h"

Stopwatch::Stopwatch() {
	Reset();
}
void Stopwatch::Reset() {
	start_time = std::chrono::high_resolution_clock::now();
}
std::uint64_t Stopwatch::Elapsed() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}
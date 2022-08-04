#pragma once
#include <random>
class Randomizer {
public:
	Randomizer() : device_(), engine_(device_()) {};
	int Random(int a, int b) {
		if (b < a)
			std::swap(a, b);
		std::uniform_int_distribution<int> uni_dist(a, b);
		return uni_dist(engine_);
	}
	double Random(double a, double b) {
		if (b < a)
			std::swap(a, b);
		std::uniform_real_distribution<double> uni_dist(a, b);
		return uni_dist(engine_);
	}
private:
	std::random_device device_;
	std::default_random_engine engine_;
};
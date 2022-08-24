#pragma once
#include <random>
class Randomizer {
public:
	Randomizer() : device_(), engine_(device_()) {};
	int Random(int min, int max) {
		if (max < min)
			std::swap(min, max);
		std::uniform_int_distribution<int> uni_dist(min, max);
		return uni_dist(engine_);
	}
	double Random(double min, double max) {
		if (max < min)
			std::swap(min, max);
		std::uniform_real_distribution<double> uni_dist(min, max);
		return uni_dist(engine_);
	}
private:
	std::random_device device_;
	std::default_random_engine engine_;
};
#include "pch.h"
#include "ParticleSystemSettingsFactory.h"
#include "PXUtilities/Randomizer.h"
namespace Factory::ParticleSystemSettings {
	Settings::ParticleSystemSettings GetSmokeSystemSettings(const sf::Vector2f& position, Size size) {
		Settings::ParticleSystemSettings result;
		Randomizer rnd;
		result.origin = position;
		double gravity_angle = rnd.Random(1.04, 2.09);
		//-sin because y axis is inverted
		result.gravity = sf::Vector2f(cos(gravity_angle), -sin(gravity_angle));
		if (size == Size::small) {
			float val = static_cast<float>(rnd.Random(50.0, 100.0));
			result.size = sf::Vector2f(val, val);
		}
		else if (size == Size::medium) {
			float val = static_cast<float>(rnd.Random(100.0, 200.0));
			result.size = sf::Vector2f(val, val);
		}
		else {
			float val = static_cast<float>(rnd.Random(200.0, 350.0));
			result.size = sf::Vector2f(val, val);
		}
		result.particle_speed = 20.0f;
		result.dissolve = true;
		result.dissolution_rate = 2;
		return result;
	}
}
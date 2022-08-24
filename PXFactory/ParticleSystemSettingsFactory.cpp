#include "pch.h"
#include "ParticleSystemSettingsFactory.h"
#include "PXUtilities/Randomizer.h"
namespace Factory::ParticleSystemSettings {
	Settings::ParticleSystemSettings GetSmokeSystemSettings(const sf::Vector2f& position, Size size) {
		Settings::ParticleSystemSettings result;
		Randomizer rnd;
		result.position = position;
		double angle = rnd.Random(1.04, 2.09);
		//-sin because y axis is inverted
		result.gravity = sf::Vector2f(cos(angle), -sin(angle));
		if (size == Size::small) {
			unsigned val = static_cast<unsigned>(rnd.Random(50, 100));
			result.size = sf::Vector2u(val, val);
		}
		else if (size == Size::medium) {
			unsigned val = static_cast<unsigned>(rnd.Random(100, 200));
			result.size = sf::Vector2u(val, val);
		}
		else {
			unsigned val = static_cast<unsigned>(rnd.Random(200, 350));
			result.size = sf::Vector2u(val, val);
		}
		result.particle_speed = 20.0f;
		result.dissolve = true;
		result.dissolution_rate = 2;
		return result;
	}
}
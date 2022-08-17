#include "pch.h"
#include "ParticleSystemSettingsFactory.h"
#include "PXUtilities/Randomizer.h"
namespace Factory::ParticleSystemSettings {
	Settings::ParticleSystemSettings GetSmokeSettings(const sf::Vector2f& position, Size size) {
		Settings::ParticleSystemSettings result;
		Randomizer rnd;
		result.position = position;
		result.gravity = sf::Vector2f(static_cast<float>(rnd.Random(-5.0, 5.0)), -5.0f);
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
		result.dissolution_rate = 1;
		return result;
	}
}
#include "Smoke.h"
#include "PXUtilities/Randomizer.h"
namespace Core::Particle {
	Smoke::Smoke(ParticleEmitter* parent, unsigned int particles, const sf::Vector2f& position, Factory::ParticleSystemSettings::Size size) :
		ParticleSystemBase(parent, Factory::ParticleSystemSettings::GetSmokeSettings(position, size), particles) {
	}
	std::unique_ptr<Particle> Smoke::CreateParticle() const {
		Settings::ParticleSettings smoke_settings;
		smoke_settings.position.x = static_cast<float>(_settings.size.x / 2);
		smoke_settings.position.x += _randomizer.Random(-static_cast<double>(_settings.size.x) / 10.0, static_cast<double>(_settings.size.x) / 10.0);
		smoke_settings.position.y = static_cast<float>(_settings.size.y);
		smoke_settings.position.y -= _randomizer.Random(.0, static_cast<double>(_settings.size.y) / 10.0);
		double angle = _randomizer.Random(1.2, 1.9);
		smoke_settings.velocity.x = _randomizer.Random(0.0, cos(angle));
		smoke_settings.velocity.y = _randomizer.Random(0.0, sin(angle));
		char value = static_cast<char>(_randomizer.Random(10, 220));
		smoke_settings.color = sf::Color(value, value, value);
		smoke_settings.timely = true;
		smoke_settings.max_time = 6.0f;
		std::unique_ptr<Particle> result = std::make_unique<Particle>(smoke_settings);
		return result;
	}
}
#include "Smoke.h"
#include "PXUtilities/Randomizer.h"
namespace Core::Particle {
	Smoke::Smoke(ParticleEmitter* parent, const sf::Vector2f& position, Factory::ParticleSystemSettings::Size size) :
		ParticleSystemBase(parent, Factory::ParticleSystemSettings::GetSmokeSystemSettings(position, size)) {
	}
	void Smoke::InitParticleSystem() {
		AddParticles(500);
	}
	std::unique_ptr<Particle> Smoke::CreateParticle() const {
		Settings::ParticleSettings smoke_settings;
		smoke_settings.position.x = static_cast<float>(_settings.size.x / 2);
		smoke_settings.position.x += _randomizer.Random(-static_cast<double>(_settings.size.x) / 25.0, static_cast<double>(_settings.size.x) / 25.0);
		smoke_settings.position.y = static_cast<float>(_settings.size.y-1);
		smoke_settings.position.y -= _randomizer.Random(.0, static_cast<double>(_settings.size.y) / 10.0);
		double velocity_angle = _randomizer.Random(1.04, 2.09);
		//-sin because y axis is inverted
		smoke_settings.velocity = sf::Vector2f(cos(velocity_angle), -sin(velocity_angle));
		smoke_settings.velocity *= static_cast<float>(_randomizer.Random(0.7, 1.5));
		char color = static_cast<unsigned char>(_randomizer.Random(150,170));
		smoke_settings.color = sf::Color(color, color, color);
		smoke_settings.timely = true;
		smoke_settings.max_time = 7.0f;
		std::unique_ptr<Particle> result = std::make_unique<Particle>(smoke_settings);
		return result;
	}
}
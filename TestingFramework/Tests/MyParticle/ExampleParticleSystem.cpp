#include "ExampleParticleSystem.h"

void Test::ExampleParticleSystem::InitParticleSystem() {
	AddParticles(1000);
}
std::unique_ptr<Core::Particle::Particle> Test::ExampleParticleSystem::CreateParticle(Randomizer& randomizer) const {
	Settings::ParticleSettings settings;
	settings.color = sf::Color{ 255,255,255,255 };
	settings.max_time = 2.0f;
	settings.position.x = randomizer.Random(.0, static_cast<double>(_settings.size.x));
	settings.position.y = randomizer.Random(.0, static_cast<double>(_settings.size.y));
	settings.timely = false;
	settings.velocity = sf::Vector2f{ .0f,.0f };
	return std::make_unique<Core::Particle::Particle>(settings);
}
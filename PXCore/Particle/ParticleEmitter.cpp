#include "ParticleEmitter.h"

Core::Particle::ParticleEmitter::ParticleEmitter(World::WorldBase* parent) :_parent{parent} {
}
void Core::Particle::ParticleEmitter::Tick(float time) {
	for (const auto& particle : _particles_systems)
		particle->Tick(time);
}
void Core::Particle::ParticleEmitter::Draw(sf::RenderWindow& window) {
	for (const auto& particle : _particles_systems)
		particle->Draw(window);
}
#include "ParticleEmitter.h"

Core::Particle::ParticleEmitter::ParticleEmitter(World::WorldBase* parent) :_parent{ parent } {
}
void Core::Particle::ParticleEmitter::Tick(float time) {
	std::lock_guard lock(_particles_systems.mtx);
	for (const auto& particle_sys : *_particles_systems.rsc)
		particle_sys->Tick(time);
}
void Core::Particle::ParticleEmitter::Draw(sf::RenderWindow& window) {
	std::lock_guard lock(_particles_systems.mtx);
	for (const auto& particle_sys : *_particles_systems.rsc)
		particle_sys->Draw(window);
}
void Core::Particle::ParticleEmitter::PushNewParticles(std::unique_ptr<ParticleSystemBase>&& particle_system) {
	std::lock_guard lock(_particles_systems.mtx);
	_particles_systems.rsc->emplace_back(std::move(particle_system));
	_particles_systems.rsc->back()->InitParticleSystem();
}
void Core::Particle::ParticleEmitter::Run(){
	using namespace std::chrono_literals;
	while (_refresh_particles_systems) {
		std::this_thread::sleep_for(1s);
		std::lock_guard lock(_particles_systems.mtx);
		auto it = std::partition(_particles_systems.rsc->begin(), _particles_systems.rsc->end(), [](const std::unique_ptr<ParticleSystemBase>& particle_system) {
			auto result= particle_system->IsValid();
			if (!result)
				particle_system->EndParticleSystem();
			return result;
			});
		_particles_systems.rsc->erase(_particles_systems.rsc->begin(), it);
	}
}
void Core::Particle::ParticleEmitter::Wait(){
	if (_thr.joinable())
		_thr.join();
}
void Core::Particle::ParticleEmitter::Terminate(){
	_refresh_particles_systems = false;
}

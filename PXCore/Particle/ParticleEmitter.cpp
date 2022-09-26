#include "ParticleEmitter.h"
#include "RepeatableParticleSystemBase.h"
namespace Core::Particle {
	ParticleEmitter::ParticleEmitter(World::WorldBase* parent) :_parent{ parent }, _thr{ std::make_unique<std::thread>(std::bind(&ParticleEmitter::Run, this)) }
	{
	}
	ParticleEmitter::~ParticleEmitter() {
		Terminate();
		Wait();
	}
	void  ParticleEmitter::Tick(float time) {
		std::lock_guard lock(_particles_systems.mtx);
		for (const auto& particle_sys : *_particles_systems.rsc)
			particle_sys->Tick(time);
	}
	void Core::Particle::ParticleEmitter::Draw(sf::RenderWindow& window) {
		std::lock_guard lock(_particles_systems.mtx);
		for (const auto& particle_system : *_particles_systems.rsc)
			window.draw(*particle_system);
	}
	void  ParticleEmitter::PushNewParticles(std::unique_ptr<ParticleSystemBase>&& particle_system) {
		std::lock_guard lock(_particles_systems.mtx);
		_particles_systems.rsc->emplace_back(std::move(particle_system));
		_particles_systems.rsc->back()->InitParticleSystem();
		if (auto repeatable_particle_system = dynamic_cast<RepeatableParticleSystemBase*>(_particles_systems.rsc->back().get()); repeatable_particle_system != nullptr)
			_time_manager.AttachToSeconds(repeatable_particle_system);
	}
	void  ParticleEmitter::Run() {
		using namespace std::chrono_literals;
		while (_refresh_particles_systems) {
			std::this_thread::sleep_for(1s);
			std::lock_guard lock(_particles_systems.mtx);
			auto it = std::partition(_particles_systems.rsc->begin(), _particles_systems.rsc->end(), [this](const std::unique_ptr<ParticleSystemBase>& particle_system) {
				auto result = particle_system->ToDelete();
				if (result) {
					particle_system->EndParticleSystem();
					if (auto repeatable_particle_system = dynamic_cast<RepeatableParticleSystemBase*>(particle_system.get()); repeatable_particle_system != nullptr)
						_time_manager.DetachFromSeconds(repeatable_particle_system);
				}
				return result;
				});
			_particles_systems.rsc->erase(_particles_systems.rsc->begin(), it);
		}
	}
	void  ParticleEmitter::Wait() {
		if (_thr->joinable())
			_thr->join();
	}
	void  ParticleEmitter::Terminate() {
		_refresh_particles_systems = false;
	}
}
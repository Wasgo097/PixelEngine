#include "ParticleSystemBase.h"
#include <future>
#include <iostream>
namespace Core::Particle {
	ParticleSystemBase::ParticleSystemBase(const Settings::ParticleSystemSettings& settings) :_settings{ settings } {
	}
	void ParticleSystemBase::AddParticles(unsigned int particles) {
		std::lock_guard lock(_particles.mtx);
		//mt particle creation
		/*const unsigned int THREAD = std::thread::hardware_concurrency() / 2;
		int particles_per_thread = particles / THREAD;
		std::list<std::future<std::list<std::unique_ptr<Particle>>>> async_particles_list;
		for (unsigned int i = 0; i < THREAD - 1; i++)
			async_particles_list.push_back(std::async(std::launch::async, &ParticleSystemBase::CreateParticles, this, particles_per_thread));
		async_particles_list.push_back(std::async(std::launch::async, &ParticleSystemBase::CreateParticles, this, particles - ((THREAD - 1) * particles_per_thread)));
		for (auto& async_particles : async_particles_list)
			_particles.splice(_particles.end(), async_particles.get());*/
			////
		_particles.rsc->splice(_particles.rsc->end(), CreateParticles(particles));
		//std::cout << "New particles size " << _particles.rsc->size() << "\n";
	}
	std::list<std::unique_ptr<Particle>> ParticleSystemBase::CreateParticles(unsigned int particles)const {
		std::list<std::unique_ptr<Particle>> result;
		Randomizer randomizer;
		for (unsigned int i = 0; i < particles; i++)
			result.push_back(CreateParticle(randomizer));
		return result;
	}
	void ParticleSystemBase::Tick(float delta) {
		std::lock_guard lock(_particles.mtx);
		for (auto& particle : *_particles.rsc)
			particle->Tick(delta, _settings.gravity, _settings.particle_speed, _settings.dissolve ? _settings.dissolution_rate : std::optional<unsigned char>());
		sf::FloatRect rect;
		rect.height = _settings.size.y;
		rect.width = _settings.size.x;
		rect.left = _settings.origin.x - (_settings.size.x / 2.0);
		rect.top = _settings.origin.y - (_settings.size.y);
		auto it = std::partition(_particles.rsc->begin(), _particles.rsc->end(), [this, rect](const std::unique_ptr<Particle>& particle) {
			return particle->ToDelete(rect);
			});
		_particles.rsc->erase(_particles.rsc->begin(), it);
		//std::cout << "Tick particles size " << _particles.rsc->size() << "\n";
	}
	bool ParticleSystemBase::ToDelete() const {
		std::lock_guard lock(_particles.mtx);
		return _particles.rsc->empty();
	}
	void ParticleSystemBase::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		std::lock_guard lock(_particles.mtx);
		unsigned int i = 0;
		sf::VertexArray vertices(sf::Points, _particles.rsc->size());
		//std::cout << "Vertices size " << vertices.getVertexCount() << " particle size "<<_particles.rsc->size()<<"\n";
		for (const auto& particle : *_particles.rsc) {
			vertices[i] = particle->GetVertex();
			i++;
		}
		target.draw(vertices, states);
	}
}
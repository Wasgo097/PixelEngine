#include "ParticleSystemBase.h"
#include <future>
namespace Core::Particle {
	ParticleSystemBase::ParticleSystemBase(const Settings::ParticleSystemSettings& settings) :_settings{ settings } {
	}
	void ParticleSystemBase::AddParticles(unsigned int particles) {
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
		_particles.splice(_particles.end(), CreateParticles(particles));
	}
	std::list<std::unique_ptr<Particle>> ParticleSystemBase::CreateParticles(unsigned int particles)const {
		std::list<std::unique_ptr<Particle>> result;
		Randomizer randomizer;
		for (unsigned int i = 0; i < particles; i++)
			result.push_back(CreateParticle(randomizer));
		return result;
	}
	void ParticleSystemBase::Tick(float delta) {
		for (auto& particle : _particles)
			particle->Tick(delta, _settings.gravity, _settings.particle_speed, _settings.dissolve ? _settings.dissolution_rate : std::optional<unsigned char>());
		sf::FloatRect rect;
		rect.height = _settings.size.y;
		rect.width = _settings.size.x;
		rect.left = _settings.origin.x - (_settings.size.x / 2.0);
		rect.top = _settings.origin.y - (_settings.size.y);
		auto it = std::partition(_particles.begin(), _particles.end(), [this, rect](const std::unique_ptr<Particle>& particle) {
			return particle->ToDelete(rect);
			});
		_particles.erase(_particles.begin(), it);
	}
	bool ParticleSystemBase::ToDelete() const {
		return _particles.empty();
	}
	void ParticleSystemBase::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (const auto& particle : _particles)
			target.draw(*particle, states);
	}
}
#include "ParticleSystemBase.h"
#include <future>
#include <iostream>
#include "PXStopwatch/Stopwatch.h"
namespace Core::Particle {
	const sf::Color ParticleSystemBase::_TRANSPARENT = sf::Color(0, 0, 0, 0);
	//Randomizer ParticleSystemBase::_randomizer = Randomizer();
	ParticleSystemBase::ParticleSystemBase(const Settings::ParticleSystemSettings& settings) :_settings{ settings } {
		_image.create(_settings.size.x, _settings.size.y, _TRANSPARENT);
		_texture.loadFromImage(_image);
		_sprite = sf::Sprite(_texture);
		_sprite.setOrigin(static_cast<float>(_settings.size.x) / 2.0f, static_cast<float>(_settings.size.y));
		_sprite.setPosition(_settings.position);
	}
	void ParticleSystemBase::AddParticles(unsigned int particles) {
		/*const unsigned int THREAD = std::thread::hardware_concurrency() / 2;
		int particles_per_thread = particles / THREAD;
		std::list<std::future<std::list<std::unique_ptr<Particle>>>> async_particles_list;
		for (unsigned int i = 0; i < THREAD - 1; i++)
			async_particles_list.push_back(std::async(std::launch::async, &ParticleSystemBase::CreateParticles, this, particles_per_thread));
		async_particles_list.push_back(std::async(std::launch::async, &ParticleSystemBase::CreateParticles, this, particles - ((THREAD - 1) * particles_per_thread)));
		for (auto& async_particles : async_particles_list)
			_particles.splice(_particles.end(), async_particles.get());*/
		_particles.splice(_particles.end(), CreateParticles(particles));
	}
	std::list<std::unique_ptr<Particle>> ParticleSystemBase::CreateParticles(unsigned int particles)const {
		std::list<std::unique_ptr<Particle>> result;
		Randomizer randomizer;
		for (unsigned int i = 0; i < particles; i++)
			result.push_back(std::move(CreateParticle(randomizer)));
		return result;
	}
	void ParticleSystemBase::Tick(float delta) {
		for (auto& particle : _particles)
			particle->Tick(delta, _settings.gravity, _settings.particle_speed, _settings.dissolve ? _settings.dissolution_rate : std::optional<unsigned char>());
		auto it = std::partition(_particles.begin(), _particles.end(), [this](const std::unique_ptr<Particle>& particle) {
			return particle->ToDelete(_settings.size);
			});
		_particles.erase(_particles.begin(), it);
	}
	void ParticleSystemBase::Draw(sf::RenderWindow& window) {
		Clear();
		PrepareTexture();
		window.draw(_sprite);
	}
	bool ParticleSystemBase::ToDelete() const {
		return _particles.size() == 0;
	}
	void ParticleSystemBase::PrepareTexture() {
		for (auto& particle : _particles)
			particle->Draw(_image);
		_texture.update(_image);
	}
	void ParticleSystemBase::Clear() {
		_image.create(_settings.size.x, _settings.size.y, _TRANSPARENT);
	}
}
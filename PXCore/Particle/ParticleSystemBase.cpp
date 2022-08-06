#include "ParticleSystemBase.h"
namespace Core::Particle {
	const sf::Color ParticleSystemBase::_TRANSPARENT = sf::Color(0, 0, 0, 0);
	ParticleSystemBase::ParticleSystemBase(const Settings::ParticleSystemSettings& settings, unsigned int particles) :_settings{ settings } {
		_image.create(_settings.size.x, _settings.size.y, _TRANSPARENT);
		_texture.loadFromImage(_image);
		_sprite = sf::Sprite(_texture);
		AddParticles(particles);
	}
	void ParticleSystemBase::AddParticles(unsigned int particles) {
		if (_particles.capacity() < _particles.size() + particles)
			_particles.reserve(_particles.capacity() + particles);
		for (unsigned int i = 0; i < particles; i++)
			_particles.emplace_back(CreateParticle());
	}
	void ParticleSystemBase::Update(float delta) {
		for (const auto& particle : _particles)
			particle->Tick(delta, _settings.gravity, _settings.particle_speed, _settings.dissolve ? _settings.dissolution_rate : std::optional<unsigned char>());
		auto it = std::partition(_particles.begin(), _particles.end(), [this](const std::unique_ptr<Particle>& particle) {
			return particle->IsValid(_settings.size);
			});
		_particles.erase(_particles.begin(), it);
	}
	void ParticleSystemBase::Draw(sf::RenderWindow& window) {
		Clear();
		PrepareTexture();
		window.draw(_sprite);
	}
	void ParticleSystemBase::PrepareTexture() {
		for (const auto& particle : _particles)
			particle->Draw(_image);
		_texture.update(_image);
	}
	void ParticleSystemBase::Clear() {
		_image.create(_settings.size.x, _settings.size.y, _TRANSPARENT);
	}
}
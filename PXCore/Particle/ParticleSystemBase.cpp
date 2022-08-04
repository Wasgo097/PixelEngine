#include "ParticleSystemBase.h"
namespace Core::Particle {
	const sf::Color ParticleSystemBase::_TRANSPARENT = sf::Color(0, 0, 0, 0);
	ParticleSystemBase::ParticleSystemBase(const sf::Vector2u& size, const sf::Vector2f& position, unsigned int particles) :_position{position} {
		_image.create(size.x, size.y, _TRANSPARENT);
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
		for (const auto& particle : _particles) {
			particle->vel.x += _gravity.x * delta;
			particle->vel.y += _gravity.y * delta;
			particle->pos.x += particle->vel.x * delta * _particle_speed;
			particle->pos.y += particle->vel.y * delta * _particle_speed;
			if (_dissolve)
				particle->color.a -= _dissolution_rate;
		}
		auto it = std::partition(_particles.begin(), _particles.end(), [this](const std::unique_ptr<Particle>& particle) {
			return particle->pos.x > _image.getSize().x or particle->pos.x < 0 or particle->pos.y > _image.getSize().y or particle->pos.y < 0 or particle->color.a < 10;
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
			_image.setPixel(static_cast<unsigned int>(particle->pos.x), static_cast<unsigned int>(particle->pos.y), particle->color);
		_texture.update(_image);
	}
	void ParticleSystemBase::Clear() {
		const auto& current_size = _image.getSize();
		_image.create(current_size.x, current_size.y, _TRANSPARENT);
	}
}
#include "ParticleSystemBase.h"
#include <SFML/Graphics/CircleShape.hpp>
//#define DEBUG
namespace Core::Particle {
	const sf::Color ParticleSystemBase::_TRANSPARENT = sf::Color(0, 0, 0, 0);
	Randomizer ParticleSystemBase::_randomizer = Randomizer();
	ParticleSystemBase::ParticleSystemBase(const Settings::ParticleSystemSettings& settings) :_settings{ settings } {
		_image.create(_settings.size.x, _settings.size.y, _TRANSPARENT);
		_texture.loadFromImage(_image);
		_sprite = sf::Sprite(_texture);
		_sprite.setOrigin(_settings.size.x / 2.0f, _settings.size.y);
		_sprite.setPosition(_settings.position);
	}
	void ParticleSystemBase::AddParticles(unsigned int particles) {
		for (unsigned int i = 0; i < particles; i++)
			_particles.push_back(std::move(CreateParticle()));
	}
	void ParticleSystemBase::Tick(float delta) {
		for (const auto& particle : _particles)
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
//#ifdef DEBUG
//		sf::CircleShape circle(1.0);
//		circle.setPosition(_settings.position);
//		circle.setFillColor(sf::Color::Black);
//		window.draw(circle);
//#endif
	}
	bool ParticleSystemBase::ToDelete() const {
		return _particles.size() == 0;
	}
	void ParticleSystemBase::PrepareTexture() {
		for (const auto& particle : _particles)
			particle->Draw(_image);
//#ifdef DEBUG
//		for (int x = 0; x < _settings.size.x; x++) {
//			_image.setPixel(x, 0, sf::Color::Black);
//			_image.setPixel(x, _settings.size.y - 1, sf::Color::Black);
//		}
//		for (int y = 0; y < _settings.size.y; y++) {
//			_image.setPixel(0, y, sf::Color::Black);
//			_image.setPixel(_settings.size.x - 2, y, sf::Color::Black);
//		}
//#endif
		_texture.update(_image);
	}
	void ParticleSystemBase::Clear() {
		_image.create(_settings.size.x, _settings.size.y, _TRANSPARENT);
	}
}
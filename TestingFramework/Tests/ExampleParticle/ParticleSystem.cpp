#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(int width, int height) {
	_image.create(width, height, _transparent);
	_texture.loadFromImage(_image);
	_sprite = sf::Sprite(_texture);
	_position.x = 0.5f * width;
	_position.y = 0.5f * height;
}
void ParticleSystem::AddParticles(unsigned int particles) {
	double angle;
	if (_particles.capacity() < _particles.size() + particles)
		_particles.reserve(_particles.capacity() + particles);
	for (unsigned int i = 0; i < particles; i++) {
		std::unique_ptr<Particle> particle(new Particle());
		particle->pos.x = _position.x;
		particle->pos.y = _position.y;
		switch (_shape)
		{
		case Shape::circle:
			angle = _randomizer.Random(0.0, 6.2832);
			particle->vel.x = _randomizer.Random(0.0, cos(angle));
			particle->vel.y = _randomizer.Random(0.0, sin(angle));
			break;
		case Shape::square:
			particle->vel.x = _randomizer.Random(-1.0, 1.0);
			particle->vel.y = _randomizer.Random(-1.0, 1.0);
			break;
		default:
			particle->vel.x = 0.5f; // Easily detected
			particle->vel.y = 0.5f; // Easily detected
		}
		if (particle->vel.x == 0.0f && particle->vel.y == 0.0f)
			continue;
		particle->color.r = _randomizer.Random(0, 255);
		particle->color.g = _randomizer.Random(0, 255);
		particle->color.b = _randomizer.Random(0, 255);
		particle->color.a = 255;
		_particles.emplace_back(std::move(particle));
	}
}
void ParticleSystem::Tick() {
	float time = _clock.restart().asSeconds();
	for (const auto& particle : _particles) {
		particle->vel.x += _gravity.x * time;
		particle->vel.y += _gravity.y * time;
		particle->pos.x += particle->vel.x * time * _particle_speed;
		particle->pos.y += particle->vel.y * time * _particle_speed;
		if (_dissolve)
			particle->color.a -= _dissolution_rate;
	}
	auto it = std::partition(_particles.begin(), _particles.end(), [this](const std::unique_ptr<Particle>& particle) {
		return particle->pos.x >= _image.getSize().x or particle->pos.x <= 0 or particle->pos.y >= _image.getSize().y or particle->pos.y <= 0 or particle->color.a <= 10;
		});
	_particles.erase(_particles.begin(), it);
}
void ParticleSystem::Render() {
	for (const auto& particle : _particles)
		_image.setPixel(static_cast<unsigned int>(particle->pos.x), static_cast<unsigned int>(particle->pos.y), particle->color);
	_texture.update(_image);
}
void ParticleSystem::Clear() {
	const auto& current_size = _image.getSize();
	_image.create(current_size.x, current_size.y, _transparent);
}
std::string ParticleSystem::getNumberOfParticlesString() {
	return std::to_string(_particles.size());
}
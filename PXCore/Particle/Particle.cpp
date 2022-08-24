#include "Particle.h"
namespace Core::Particle {
	Particle::Particle(const Settings::ParticleSettings& settings, std::optional<std::function<void()>> OnElapsed)
		:_position{ settings.position }, _velocity{ settings.velocity }, _color{ settings.color }, _TIMELY{ settings.timely }, _MAX_TIME{ settings.max_time }, _time{ .0f }, _current_dissolution{static_cast<float>(_color.a)}{
		if (OnElapsed)
			this->OnElapsed = *OnElapsed;
	}
	void Particle::Tick(float delta, const sf::Vector2f& gravity, float particle_speed, std::optional<unsigned char> dissolution_rate) {
		if (this->_time += delta >= _MAX_TIME) {
			if (OnElapsed) {
				OnElapsed();
				return;
			}
		}
		_velocity.x += gravity.x * delta;
		_velocity.y += gravity.y * delta;
		_position.x += _velocity.x * delta * particle_speed;
		_position.y += _velocity.y * delta * particle_speed;
		if (dissolution_rate) {
			_current_dissolution -= static_cast<float>(*dissolution_rate) * delta;
			_color.a = static_cast<unsigned char>(_current_dissolution);
		}
		_time += delta;
	}
	void Particle::Draw(sf::Image& image) {
		sf::Vector2u coord{ static_cast<unsigned>(_position.x),static_cast<unsigned>(_position.y) };
		image.setPixel(coord.x, coord.y, _color);
	}
	bool Particle::ToDelete(const sf::Vector2u& image_size) const {
		auto condition =
			_position.x >= image_size.x - 1
			or _position.x <= 0
			or _position.y >= image_size.y - 1
			or _position.y <= 0
			or _color.a <= 10;
		if (_TIMELY)
			condition = condition or _time >= _MAX_TIME;
		return condition;
	}
}
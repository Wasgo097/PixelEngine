#include "Particle.h"
namespace Core::Particle {
	Particle::Particle(const Settings::ParticleSettings& settings, std::optional<std::function<void()>> OnElapsed)
		: _velocity{ settings.velocity },
		_TIMELY{ settings.timely },
		_MAX_TIME{ settings.max_time },
		_time{ .0f },
		_current_dissolution{ static_cast<float>(settings.color.a) } {
		_vertex.color = settings.color;
		_vertex.position = settings.origin;
		if (OnElapsed)
			this->OnElapsed = *OnElapsed;
	}
	void Particle::Tick(float delta, const sf::Vector2f& gravity, float particle_speed, std::optional<unsigned char> dissolution_rate) {
		if (_time >= _MAX_TIME and OnElapsed) {
			OnElapsed();
			return;
		}
		_velocity.x += gravity.x * delta;
		_velocity.y += gravity.y * delta;
		_vertex.position.x += _velocity.x * delta * particle_speed;
		_vertex.position.y += _velocity.y * delta * particle_speed;
		if (dissolution_rate) {
			_current_dissolution -= static_cast<float>(*dissolution_rate) * delta;
			_vertex.color.a = static_cast<unsigned char>(_current_dissolution);
		}
		_time += delta;
	}
	void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(&_vertex, 1, sf::Points, states);
	}
	bool Particle::ToDelete(const sf::Vector2f& range) const {
		auto delete_condition =
			_vertex.position.x >= range.x
			or _vertex.position.x <= 0.0
			or _vertex.position.y >= range.y - 1
			or _vertex.position.y <= 0.0
			or _vertex.color.a < 10;
		if (_TIMELY)
			delete_condition = delete_condition or _time >= _MAX_TIME;
		return delete_condition;
	}
}
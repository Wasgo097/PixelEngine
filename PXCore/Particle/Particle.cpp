#include "Particle.h"
namespace Core::Particle {
	Particle::Particle(const Settings::ParticleSettings& settings, std::optional<std::function<void()>> OnElapsed)
		:position{ settings.position }, velocity{ settings.velocity }, color{ settings.color }, timely{ settings.timely }, max_time{ settings.max_time }, time{ .0f }{
		if (OnElapsed)
			this->OnElapsed = *OnElapsed;
	}
	void Particle::Tick(float delta, const sf::Vector2f& gravity, float particle_speed, std::optional<unsigned char> dissolution_rate) {
		if (this->time += delta < max_time) {
			if (OnElapsed)
				OnElapsed();
			return;
		}
		velocity.x += gravity.x * delta;
		velocity.y += gravity.y * delta;
		position.x += velocity.x * delta * particle_speed;
		position.y += velocity.y * delta * particle_speed;
		if (dissolution_rate)
			color.a -= *dissolution_rate;
	}
	void Particle::Draw(sf::Image& image) {
		image.setPixel(static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y), color);
	}
	bool Particle::IsValid(const sf::Vector2u& image_size) const {
		auto validation = position.x > image_size.x or position.x < 0 or position.y > image_size.y or position.y < 0 or color.a < 10;
		if (timely)
			validation = validation or this->time < max_time;
		return validation;
	}
}
#pragma once
#include <SFML/System/Vector2.hpp>
namespace Settings {
	struct ParticleSystemSettings {
		ParticleSystemSettings(const sf::Vector2f& position, const sf::Vector2f& gravity, const sf::Vector2u& size, float particle_speed, bool dissolve, unsigned char dissolution_rate)
			:position{ position }, gravity{ gravity }, size{ size }, particle_speed{ particle_speed }, dissolve{ dissolve }, dissolution_rate{ dissolution_rate }{}
		ParticleSystemSettings() = default;

		bool operator==(const ParticleSystemSettings& obj)const {
			return position == obj.position and gravity == obj.gravity and size == obj.size and particle_speed == obj.particle_speed and dissolve == obj.dissolve and dissolution_rate == obj.dissolution_rate;
		}

		sf::Vector2f position;
		sf::Vector2f gravity;
		sf::Vector2u size;
		float particle_speed = 1.0f;
		bool dissolve = false;
		unsigned char dissolution_rate = 1;
	};
}
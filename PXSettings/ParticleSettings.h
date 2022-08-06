#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
namespace Settings {
	struct ParticleSettings {
		ParticleSettings(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Color& color, bool timely, float max_time)
			:position{ position }, velocity{ velocity }, color{ color }, timely{ timely }, max_time{ max_time }{}
		ParticleSettings() = default;

		bool operator==(const ParticleSettings& obj)const {
			return position == obj.position and velocity == obj.velocity and color == obj.color and timely == obj.timely and max_time == obj.max_time;
		}

		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Color color;
		bool timely = false;
		const float max_time = .0f;
	};
}
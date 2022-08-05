#pragma once
#include <SFML/System/Vector2.hpp>
namespace Settings {
	struct MusicSettings {
		sf::Vector2f _position;
		sf::Vector2f _gravity;
		float particle_speed = 20.0f;
		bool _dissolve = false;
		unsigned char _dissolution_rate = 4;
	};
}

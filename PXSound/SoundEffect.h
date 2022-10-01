#pragma once
#include <SFML/Audio.hpp>
namespace Sound {
	class SoundEffect {
	public:
		SoundEffect(const sf::SoundBuffer& buffer);
		bool IsValid()const;
	protected:
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
	};
}
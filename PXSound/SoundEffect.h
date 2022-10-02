#pragma once
#include <SFML/Audio.hpp>
namespace Sound {
	class SoundEffect {
	public:
		SoundEffect(const sf::SoundBuffer& buffer);
		~SoundEffect();
		void SetBuffer(sf::SoundBuffer&& new_buffer);
		bool IsValid()const;
		void Play();
		void Stop();
		void SetVolume(float new_volume);
	protected:
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
	};
}
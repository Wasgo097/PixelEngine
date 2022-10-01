#pragma once
#include <memory>
#include <SFML/Audio.hpp>
namespace Sound {
	class MusicManager {
	public:
		void SetVolume(float new_volume)const;
		void PlayMusic(std::unique_ptr<sf::Music>&& new_music);
	protected:
		std::unique_ptr<sf::Music> _current_playing_music;
	};
}
#pragma once
#include <memory>
#include <SFML/Audio.hpp>
#include <PXSettings/MusicSettings.h>
namespace Sound {
	class MusicManager {
	public:
		MusicManager(const Settings::MusicSettings& settings);
		void SetVolume(float new_volume)const;
		void PlayMusic(std::unique_ptr<sf::Music>&& new_music);
		void StopMusic()const;
		void PauseMusic()const;
	protected:
		std::unique_ptr<sf::Music> _current_playing_music;
		const Settings::MusicSettings& _settings;
	};
}
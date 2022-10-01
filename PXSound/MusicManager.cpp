#include "MusicManager.h"
namespace Sound {
	void MusicManager::SetVolume(float new_volume) const {
		if (_current_playing_music)
			_current_playing_music->setVolume(new_volume);
	}
	void MusicManager::PlayMusic(std::unique_ptr<sf::Music>&& new_music) {
		if (!_current_playing_music) {
			_current_playing_music = std::move(new_music);
			_current_playing_music->play();
			return;
		}
		_current_playing_music->pause();
		_current_playing_music = std::move(new_music);
		_current_playing_music->play();
	}
}
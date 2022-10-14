#include "MusicManager.h"
namespace Sound {
	MusicManager::MusicManager(const Settings::MusicSettings& settings) :_settings{ settings }
	{
	}
	void MusicManager::SetVolume(float new_volume) const {
		if (_current_playing_music)
			_current_playing_music->setVolume(100.0f*new_volume);
	}
	void MusicManager::PlayMusic(std::unique_ptr<sf::Music>&& new_music) {
		if (_current_playing_music)
			_current_playing_music->pause();
		_current_playing_music = std::move(new_music);
		_current_playing_music->setLoop(true);
		SetVolume(_settings.master_vol * _settings.music_vol);
		_current_playing_music->play();
	}
	void MusicManager::StopMusic()const {
		_current_playing_music->stop();
	}
	void MusicManager::PauseMusic() const {
		_current_playing_music->pause();
	}
}
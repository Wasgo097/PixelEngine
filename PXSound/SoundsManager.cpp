#include "SoundsManager.h"
namespace Sound {
	SoundsManager::SoundsManager(const Settings::MusicSettings& settings) :_settings{ settings } {
		_sounds_effects.reserve(250);
	}
	void SoundsManager::ClearSoundsEffects() {
		_sounds_effects.clear();
	}
	bool SoundsManager::PlaySoundEffect(const std::shared_ptr<SoundEffect>& new_sound_effect) {
	}
}
#include "SoundsManager.h"
#include <algorithm>
namespace Sound {
	SoundsManager::SoundsManager(const Settings::MusicSettings& settings, size_t max_buffer_size) :_settings{ settings } {
		_sounds_effects.reserve(max_buffer_size);
	}
	void SoundsManager::ClearSoundsEffects() {
		_sounds_effects.clear();
	}
	bool SoundsManager::PlaySoundEffect(const std::shared_ptr<SoundEffect>& new_sound_effect) {
		if (_sounds_effects.size() == _sounds_effects.capacity()) {
			ClearUselessEffects();
			if (_sounds_effects.size() == _sounds_effects.capacity())
				return false;
		}
		_sounds_effects.push_back(new_sound_effect);
		new_sound_effect->SetVolume(_settings.master_vol*_settings.effect_vol);
		new_sound_effect->Play();
		return true;
	}
	void SoundsManager::ClearUselessEffects() {
		auto it = std::partition(_sounds_effects.begin(), _sounds_effects.end(), [](const std::shared_ptr<SoundEffect>& effect) {
			return !effect->IsValid();
			});
		_sounds_effects.erase(_sounds_effects.begin(), it);
	}
}
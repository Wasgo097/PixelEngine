#pragma once
#include "SoundEffect.h"
#include <vector>
#include <memory> 
#include "PXSettings/MusicSettings.h"
namespace Sound {
	class SoundsManager {
	public:
		SoundsManager(const Settings::MusicSettings& settings,size_t max_buffer_size);
		void ClearSoundsEffects();
		bool PlaySoundEffect(const std::shared_ptr<SoundEffect>& new_sound_effect);
	protected:
		void ClearUselessEffects();
		std::vector<std::shared_ptr<SoundEffect>> _sounds_effects;
		const Settings::MusicSettings& _settings;
	};
}
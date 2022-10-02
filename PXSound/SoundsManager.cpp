#include "SoundsManager.h"
#include <algorithm>
#include <chrono>
#include <functional>
using namespace std::chrono_literals;
namespace Sound {
	SoundsManager::SoundsManager(const Settings::MusicSettings& settings, size_t max_buffer_size) :
		_settings{ settings },
		_gc_thread{ std::make_unique<std::thread>(std::bind(&SoundsManager::Run,this)) } {
		_sounds_effects.rsc->reserve(max_buffer_size);
	}
	SoundsManager::~SoundsManager() {
		Terminate();
		Wait();
	}
	void SoundsManager::ClearSoundsEffects() {
		std::lock_guard lock(_sounds_effects.mtx);
		_sounds_effects.rsc->clear();
	}
	bool SoundsManager::PlaySoundEffect(const std::shared_ptr<SoundEffect>& new_sound_effect) {
		std::lock_guard lock(_sounds_effects.mtx);
		if (_sounds_effects.rsc->size() == _sounds_effects.rsc->capacity()) {
			ClearUselessEffects();
			if (_sounds_effects.rsc->size() == _sounds_effects.rsc->capacity())
				return false;
		}
		_sounds_effects.rsc->push_back(new_sound_effect);
		new_sound_effect->SetVolume(_settings.master_vol * _settings.effect_vol);
		new_sound_effect->Play();
		return true;
	}
	void SoundsManager::ClearUselessEffects() {
		std::lock_guard lock(_sounds_effects.mtx);
		auto it = std::partition(_sounds_effects.rsc->begin(), _sounds_effects.rsc->end(), [](const std::shared_ptr<SoundEffect>& effect) {
			return !effect->IsValid();
			});
		_sounds_effects.rsc->erase(_sounds_effects.rsc->begin(), it);
	}
	void SoundsManager::Run() {
		while (!_terminate) {
			std::this_thread::sleep_for(50ms);
			ClearUselessEffects();
		}
	}
	void SoundsManager::Wait() {
		if (_gc_thread->joinable())
			_gc_thread->join();
	}
	void SoundsManager::Terminate() {
		_terminate = true;
	}
}
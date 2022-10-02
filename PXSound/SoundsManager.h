#pragma once
#include "PXUtilities/Interfaces/ILoopingThread.h"
#include <vector>
#include <memory>
#include <atomic>
#include <thread>
#include "PXSettings/MusicSettings.h"
#include "PXUtilities/ThreadingResource.h"
#include "SoundEffect.h"
namespace Sound {
	class SoundsManager : ILoopingThread {
	public:
		SoundsManager(const Settings::MusicSettings& settings, size_t max_buffer_size);
		void ClearSoundsEffects();
		bool PlaySoundEffect(const std::shared_ptr<SoundEffect>& new_sound_effect);
		// Inherited via ILoopingThread
		virtual void Run() override;
		virtual void Wait() override;
		virtual void Terminate() override;
	protected:
		void ClearUselessEffects();
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<SoundEffect>>> _sounds_effects;
		std::unique_ptr<std::thread> _gc_thread;
		const Settings::MusicSettings& _settings;
		std::atomic_bool _terminate{ false };
	};
}
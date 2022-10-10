#pragma once
#include "PXCore/Engine.h"
namespace Test {
	class BaseEngine :public Core::Engine {
	public:
		// Inherited via Engine
		virtual void InitEngine() override;
		virtual void OnNewWindowSettings(const Settings::WindowSettingsDTO& new_window_settings)override {}
		virtual void OnNewMusicSettings(const Settings::MusicSettings& new_music_settings)override {}
	};
}
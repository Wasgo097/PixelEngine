#pragma once
#include "PXCore/Engine.h"
namespace Test {
	class EngineForAnimationTest :public Core::Engine {
	protected:
		virtual void InitEngine()override;
		virtual void OnNewWindowSettings(const Settings::WindowSettingsDTO& new_window_settings)override {}
		virtual void OnNewMusicSettings(const Settings::MusicSettings& new_music_settings)override {}
	};
}

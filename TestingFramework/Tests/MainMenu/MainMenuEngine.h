#pragma once
#include "PXCore/Engine.h"
namespace Test {
	class MainMenuEngine:public Core::Engine{
	public:
		MainMenuEngine(std::optional<std::reference_wrapper<const ArgumentParser>> parser = {});
	protected:
		// Inherited via Engine
		virtual void InitEngine() override;
		virtual void OnNewWindowSettings(const Settings::WindowSettingsDTO& new_window_settings)override;
		virtual void OnNewMusicSettings(const Settings::MusicSettings& new_music_settings)override {}
	};
}

#pragma once
#include "PXCore/World/WorldBaseGUI.h"
#include "PXSettings/WindowSettingsDTO.h"
#include "PXSettings/MusicSettings.h"
namespace Test {
	class MainMenuWorld :public Core::World::WorldBaseGUI {
	public:
		MainMenuWorld(Settings::WindowSettingsDTO& window_settings, Settings::MusicSettings& music_settings, const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Core::Engine* parent = nullptr);
	protected:
		virtual void CheckQuit() override {}
		virtual void InitGuiSettup() override;
		virtual void InitWorld()override;
		virtual void CreateWorldBaseGUIComponents() override;
	private:
		void MainMenuPage();
		void NewGameClick();
		void SettingsWindowPage();
		void ExitClick();
		void ReturnClick();
		void RewriteWorkingWindowSettings();
		void ApplyWindowSettings();
		const Settings::WindowSettingsDTO& _window_settings;
		const Settings::MusicSettings& _music_settings;
		std::unique_ptr<Settings::WindowSettingsDTO> _working_window_settings;
		std::unique_ptr<Settings::MusicSettings> _working_music_settings;
		tgui::Tabs::Ptr _resolutions_tabs;
		tgui::Slider::Ptr _fps_slider;
		tgui::RadioButton::Ptr _fullscreen_radio;
		tgui::RadioButton::Ptr _window_radio;
		tgui::Slider::Ptr _music_slider;
		tgui::Slider::Ptr _effect_slider;
		tgui::Slider::Ptr _master_slider;
	};
}
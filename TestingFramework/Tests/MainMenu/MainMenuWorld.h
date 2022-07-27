#pragma once
#include "PXCore/World/WorldBaseGUI.h"
#include "PXSettings/WindowSettingsDTO.h"
namespace Test {
	class MainMenuWorld :public Core::World::WorldBaseGUI {
	public:
		MainMenuWorld(Settings::WindowSettingsDTO& window_settings, const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Core::Engine* parent = nullptr);
	protected:
		virtual void CheckQuit() override {};
		virtual bool InitGuiSettup() override;
		virtual void InitWorld()override;
	private:
		void MainMenuPage();
		void NewGameClick();
		void SettingsPage();
		void ExitClick();
		void ReturnClick();
		void RewriteSettings();
		void ApplySettings();
		const Settings::WindowSettingsDTO& _window_settings;
		std::unique_ptr<Settings::WindowSettingsDTO> _working_window_settings;
		tgui::Tabs::Ptr _resolutions_tabs;
		tgui::Slider::Ptr _fps_slider;
		tgui::RadioButton::Ptr _fullscreen_radio;
		tgui::RadioButton::Ptr _window_radio;

	};
}
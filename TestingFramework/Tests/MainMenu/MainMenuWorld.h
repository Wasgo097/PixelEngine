#pragma once
#include <TGUI/TGUI.hpp>
#include "PXCore/World/WorldBase.h"
#include "PXSettings/WindowSettingsDTO.h"
namespace Test {
	class MainMenuWorld :public Core::World::WorldBase {
	public:
		MainMenuWorld(Settings::WindowSettingsDTO& window_settings, const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Core::Engine* parent = nullptr);
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void ServiceGUIInput(const sf::Event& action)override;
	protected:
		// Inherited via WorldBase
		virtual void CheckQuit() override {};
		virtual void InitWorld()override;
	private:
		void CommonGuiSettup();
		void DefaultGuiSettup();
		void NewGameClick();
		void SettingsClick();
		void ExitClick();
		void ReturnClick();
		void RewriteSettings();
		void ApplySettings();
		tgui::Gui _gui;
		const Settings::WindowSettingsDTO& _window_settings;
		std::unique_ptr<Settings::WindowSettingsDTO> _working_window_settings;
		tgui::Tabs::Ptr _resolutions_tabs;
		tgui::Slider::Ptr _fps_slider;
		tgui::RadioButton::Ptr _fullscreen_radio;
		tgui::RadioButton::Ptr _window_radio;
	};
}
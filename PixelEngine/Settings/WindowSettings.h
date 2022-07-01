#pragma once
#include "SettingsBase.h"
#include "Utility/BasicSFMLTypesToJson.h"
#include <SFML/Window.hpp>
namespace Settings {
	struct WindowSettings :public SettingsBase {
		WindowSettings(sf::VideoMode mode, int fps, unsigned int style, std::string win_name, bool vsync) :video_mode{ mode }, fps{ fps }, display_style{ style }, window_name{ win_name }, vsync{ vsync } {}
		WindowSettings() = default;
		virtual std::string ToStdString()const override;
		sf::VideoMode video_mode;
		int fps = 30;
		unsigned int display_style = sf::Style::Fullscreen;
		std::string window_name = "Window";
		bool vsync = false;
		bool operator ==(const WindowSettings& obj)const {
			return (video_mode == obj.video_mode) &&
				(fps == obj.fps) &&
				(display_style == obj.display_style) &&
				(window_name == obj.window_name) &&
				(vsync == obj.vsync);
		}
	};
}

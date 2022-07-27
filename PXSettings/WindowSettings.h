#pragma once
#include "WindowSettingsDTO.h"
namespace Settings {
	struct WindowSettings :public WindowSettingsDTO {
		WindowSettings(sf::VideoMode mode, int fps, unsigned int style, bool vsync, const std::string& win_name) : WindowSettingsDTO(mode, fps, style, vsync), window_name{ win_name }{}
		WindowSettings() = default;

		bool operator ==(const WindowSettings& obj)const {
			return (video_mode == obj.video_mode) &&
				(fps == obj.fps) &&
				(display_style == obj.display_style) &&
				(window_name == obj.window_name) &&
				(vsync == obj.vsync);
		}

		std::string window_name = "Window";
	};
}

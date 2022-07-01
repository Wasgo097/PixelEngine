#pragma once
#include <string>
#include <SFML/Window/VideoMode.hpp>
namespace Settings {
	struct WindowSettings{
		WindowSettings(sf::VideoMode mode, int fps, unsigned int style, std::string win_name, bool vsync) :video_mode{ mode }, fps{ fps }, display_style{ style }, window_name{ win_name }, vsync{ vsync } {}
		WindowSettings() = default;

		bool operator ==(const WindowSettings& obj)const {
			return (video_mode == obj.video_mode) &&
				(fps == obj.fps) &&
				(display_style == obj.display_style) &&
				(window_name == obj.window_name) &&
				(vsync == obj.vsync);
		}

		sf::VideoMode video_mode;
		int fps = 30;
		unsigned int display_style = sf::Style::Fullscreen;
		std::string window_name = "Window";
		bool vsync = false;
	};
}

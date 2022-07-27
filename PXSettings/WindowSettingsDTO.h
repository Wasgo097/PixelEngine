#pragma once
#include <string>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
namespace Settings {
	struct WindowSettingsDTO {
		WindowSettingsDTO(sf::VideoMode mode, int fps, unsigned int style,  bool vsync) :video_mode{ mode }, fps{ fps }, display_style{ style }, vsync{ vsync } {}
		WindowSettingsDTO() = default;

		bool operator ==(const WindowSettingsDTO& obj)const {
			return (video_mode == obj.video_mode) &&
				(fps == obj.fps) &&
				(display_style == obj.display_style) &&
				(vsync == obj.vsync);
		}

		sf::VideoMode video_mode;
		int fps = 30;
		unsigned int display_style = sf::Style::Fullscreen;
		bool vsync = false;
	};
}
